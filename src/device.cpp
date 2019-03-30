/*  Copyright (c) 2019, spaceape
    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
    conditions are met:
    1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
    disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
    disclaimer in the documentation and/or other materials provided with the distribution.
    3. All advertising materials mentioning features or use of this software must display the following acknowledgement:
    This product includes software developed by the organization.
    4. Neither the name of the organization nor the names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY SPACEAPE ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
    THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL WICKED
    SYSTEMS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "command.h"
#include "error.h"
#include "device.h"
#include "mmio.h"
#include "uart.h"
#include "syntax.h"

      device::device() noexcept:
      m_run_bit(1),
      m_wait_bit(0),
      m_reset_bit(0),
      m_error_bit(0),
      m_phase_ctr(0)
{
      setup();
      restore();
}

      device::~device()
{
}

      device::virtual_t::virtual_t() noexcept:
      channel()
{
}

      device::virtual_t::~virtual_t()
{
}

      device::digital_out_t::digital_out_t() noexcept:
      channel()
{
}

      device::digital_out_t::~digital_out_t()
{
}

      device::analog_in_t::analog_in_t() noexcept:
      channel()
{
}

      device::analog_in_t::~analog_in_t()
{
}

      device::analog_out_t::analog_out_t() noexcept:
      channel()
{
}

      device::analog_out_t::~analog_out_t()
{
}

uint8_t device::get_channel(uint8_t) noexcept
{
      return 0;
}

uint8_t device::get_register(uint8_t) noexcept
{
      return 0;
}

bool  device::acknowledge() noexcept
{
      uart::send(tag_acknowledge);
      return true;
}

int   device::emit(uint8_t data) noexcept
{
      uart::send(data);
      return 1;
}

int   device::emit(uint8_t* data, unsigned long int length) noexcept
{
      if(data) {
          for(unsigned long int index = 0; index < length; index++) {
              uart::send(data[index]);
          }
          return length;
      }
      return 0;
}

/* recall()
 * reset device to factory settings
*/
void  device::recall() noexcept
{
      reset();
      save();
}

/* reset()
 * reinitialise device
*/
void  device::reset() noexcept
{
}

/* restore()
 * reload device state from EEPROM
*/
void  device::restore() noexcept
{
      reset();
}

/* save()
 * save device state to EEPROM
*/
void  device::save() noexcept
{
}

void  device::error(uint8_t code, ...) noexcept
{
      uart::send(tag_error);
      uart::send(code);
      uart::send(0);
      uart::send(0);
}

void  device::recover() noexcept
{
      m_error_bit = 0;
}

void  device::setup() noexcept
{
      DDRB =_BV(PORTB5);
}

//clock input
//add interrupt function
void  device::loop() noexcept
{
      do {
          uint8_t cmd;
          if(uart::recv(cmd)) {
              uint8_t op = cmd & _op;
              switch(op) {
                case nop: {
                }
                    break;
                case op_resume:
                      m_run_bit = 1;
                      m_wait_bit = 0;
                      break;
                case op_set_mode: {
                    uint8_t mode;
                    uint8_t port = cmd & _index;
                    if(uart::get_uint8(mode)) {
                        if(port >= gpio_min) {
                            if(port <= gpio_max) {
                                mmio::get_gpio_mode(port) |= mode;
                            } else
                                error(err_bad_port, port);
                        } else
                            error(err_bad_port, port);
                    } else
                        error(err_recv_fault);
                }
                    break;
                case op_set_bit: {
                    uint8_t bit;
                    uint8_t port = cmd & _index;
                    if(uart::get_uint8(bit)) {
                        if(port >= gpio_min) {
                            if(port <= gpio_max) {
                                mmio::get_gpio_port(port) |= bit;
                            } else
                                error(err_bad_port, port);
                        } else
                            error(err_bad_port, port);
                    } else
                        error(err_recv_fault);
                }
                      break;
                case op_clr_bit: {
                    uint8_t bit;
                    uint8_t port = cmd & _index;
                    if(uart::get_uint8(bit)) {
                        if(port >= gpio_min) {
                            if(port <= gpio_max) {
                                mmio::get_gpio_port(port) &=~bit;
                            } else
                                error(err_bad_port, port);
                        } else
                            error(err_bad_port, port);
                    } else
                        error(err_recv_fault);
                }
                      break;
                case op_set_analog:
                      break;
                case op_wait:
                      m_run_bit = 0;
                      m_wait_bit = 1;
                      break;
                case op_suspend:
                      m_run_bit = 0;
                      break;
                case op_zero:
                case op_reset:
                case op_halt:
                default:
                      error(err_bad_op);
                      break;
              };
          }
          if(m_error_bit) {
              recover();
          } else
              acknowledge();
      }
      while(1);
}

void  device::sync() noexcept
{
      if(m_run_bit) {
          if(m_reset_bit) {
              m_reset_bit = 0;
          }
          if(m_phase_ctr == phase_max) {
              m_phase_ctr  = phase_min;
          }
          // if constexpr (enable_gpr) {
          //     for(auto iter = std::addressof(m_gp0a); iter <= std::addressof(m_gp1h); iter++) {
          //         iter->sync();
          //     }
          // }
          // if constexpr (enable_digital) {
          //     for(auto iter = std::addressof(m_digital_0); iter <= std::addressof(m_digital_7); iter++) {
          //         iter->sync();
          //     }
          // }
          // if constexpr (enable_analog) {
          //     for(auto iter = std::addressof(m_analog_0); iter <= std::addressof(m_analog_7); iter++) {
          //         iter->sync();
          //     }
          // }
          m_phase_ctr += phase_step;
      }
}
