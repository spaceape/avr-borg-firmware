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
      m_ready_bit(1),
      m_phase_ctr(0)
{
      setup();
      restore();
}

      device::~device()
{
}

      device::virtual_t::virtual_t() noexcept:
      m_value(0)
{
}

      device::virtual_t::~virtual_t()
{
}

uint8_t device::virtual_t::get() const noexcept
{
      return m_value;
}

uint8_t* device::virtual_t::get_ptr() noexcept
{
      return std::addressof(m_value);
}

void  device::virtual_t::set(uint8_t value) noexcept
{
      m_value = value;
}

      device::digital_out_t::digital_out_t() noexcept:
      channel()
{
}

      device::digital_out_t::~digital_out_t()
{
}

bool  device::digital_out_t::setup(device* root, uint8_t function) noexcept
{
      switch(m_function) {
        case fn_none: {
        }
            break;
        case fn_pulse: {
              bool b0 = uart::recv(m_data.counter.period, m_data.counter.phase);
              if(root) {
                  bool b1 = root->get_io_pin(m_data.counter.output);
                  if(b1) {
                  }
              }
        }
            break;
        case fn_data: {
        }
            break;
        case fn_soft_pwm: {
        }
            break;
        case fn_soft_spi: {
        }
            break;
        case fn_3_phase: {
        }
            break;
        case fn_4_phase: {
        }
            break;
      }
      return false;
}

void  device::digital_out_t::sync(unsigned int) noexcept
{
      switch(m_function) {
        case fn_none: {
        }
            break;
        case fn_pulse: {
        }
            break;
        case fn_data: {
        }
            break;
        case fn_soft_pwm: {
        }
            break;
        case fn_soft_spi: {
        }
            break;
        case fn_3_phase: {
        }
            break;
        case fn_4_phase: {
        }
            break;
      }
}

      device::analog_in_t::analog_in_t() noexcept:
      channel()
{
}

void  device::analog_in_t::sync(unsigned int) noexcept
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

bool  device::analog_out_t::setup(device*, uint8_t) noexcept
{
      return false;
}

void  device::analog_out_t::sync(unsigned int) noexcept
{
}

port_t* device::get_port(uint8_t index) noexcept
{
      return std::addressof(mmio::get_gpio_port(index));
}

device::virtual_t* device::get_register(uint8_t index) noexcept
{
      return std::addressof(m_virtual[index]);
}

device::digital_out_t* device::get_digital_out(uint8_t index) noexcept
{
      return std::addressof(m_digital[index]);
}

device::analog_in_t* device::get_analog_in(uint8_t index) noexcept
{
      return std::addressof(m_analog_in[index]);
}

device::analog_out_t* device::get_analog_out(uint8_t index) noexcept
{
      return std::addressof(m_analog_out[index]);
}

/* get_io_pin()
 * obtain a mmio address and a bit mask from an uart port parameter
*/
bool  device::get_io_pin(pin_t& pin) noexcept
{
      uint8_t output;
      uint8_t bit;
      if(uart::recv(output, bit)) {
          uint8_t index = output & _at_index;
          if(output & at_register) {
              if(index < virtual_channel_count) {
                  pin.m_port = get_register(index)->get_ptr();
                  if(bit < gpio_port_size) {
                      pin.m_bit = 1 << bit;
                      pin.m_aux = 0;
                      return true;
                  }
              }
          } else
          if(index >= gpio_min) {
              if(index <= gpio_max) {
                  pin.m_port = get_port(index);
                  if(bit < gpio_port_size) {
                      pin.m_bit = 1 << bit;
                      pin.m_aux = 0;
                      return true;
                  }
              }
          }
      }
      return false;
}

bool  device::acknowledge() noexcept
{
      if constexpr (enable_acknowledge) {
          uart::send(tag_acknowledge);
      }
      return true;
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

bool  device::error(uint8_t code, ...) noexcept
{
      uart::send(tag_error);
      uart::send(code);
      uart::send(0);
      uart::send(0);
      m_ready_bit = 0;
      return false;
}

void  device::recover() noexcept
{
      m_ready_bit = 1;
}

void  device::setup() noexcept
{
}

void  device::loop() noexcept
{
      do {
          uint8_t cmd;
          if(uart::recv(cmd)) {
              uint8_t op = cmd & _op;
              switch(op) {
                case nop:
                    break;
                case op_resume:
                    m_run_bit = 1;
                    m_wait_bit = 0;
                    break;
                case op_get_mode: {
                    uint8_t port;
                    if(uart::recv(port)) {
                        if(port >= gpio_min) {
                            if(port <= gpio_max) {
                                uart::send(tag_response, op, mmio::get_gpio_mode(port));
                            } else
                                error(err_bad_port, port);
                        } else
                            error(err_bad_port, port);
                    } else
                        error(err_recv_fault);
                }
                    break;
                case op_set_mode: {
                    uint8_t port;
                    uint8_t mode;
                    if(uart::recv(port, mode)) {
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
                case op_get_bit: {
                    uint8_t port;
                    if(uart::recv(port)) {
                        if(port >= gpio_min) {
                            if(port <= gpio_max) {
                                uart::send(tag_response, op, mmio::get_gpio_pin(port));
                            } else
                                error(err_bad_port, port);
                        } else
                            error(err_bad_port, port);
                    } else
                        error(err_recv_fault);
                }
                    break;
                case op_set_bit: {
                    uint8_t port;
                    uint8_t bit;
                    if(uart::recv(port, bit)) {
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
                    uint8_t port;
                    uint8_t bit;
                    if(uart::recv(port, bit)) {
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
                case op_get_register: {
                    uint8_t reg;
                    if(uart::recv(reg)) {
                        if(reg < virtual_channel_count) {
                            uart::send(tag_response, op, m_virtual[reg].get());
                        } else
                            error(err_bad_register, reg);
                    } else
                        error(err_recv_fault);
                }
                      break;
                case op_set_register: {
                    uint8_t reg;
                    if(uart::recv(reg)) {
                        if(reg < virtual_channel_count) {
                            uint32_t value;
                            if(uart::recv(value)) {
                                m_virtual[reg].set(value);
                            } else
                                error(err_recv_fault);
                        } else
                            error(err_bad_register, reg);
                    } else
                        error(err_recv_fault);
                }
                      break;
                case op_set_input: {
                      error(err_recv_fault);
                }
                      break;
                case op_set_output: {
                      error(err_recv_fault);
                }
                      break;
                case op_set_function: {
                      uint8_t channel;
                      uint8_t function;
                      if(uart::recv(channel, function)) {
                          if(channel & ac_digital) {
                              if(channel < digital_channel_count) {
                                  if(m_digital[channel].has_function(fn_none)) {
                                      m_digital[channel].setup(this, function) || error(err_bad_op);
                                  } else
                                      error(err_busy_channel);
                              } else
                                  error(err_bad_channel);
                          } else
                          if(channel & ac_analog) {
                              if(channel < analog_output_count) {
                                  if(m_analog_out[channel].has_function(fn_none)) {
                                      m_analog_out[channel].setup(this, function) || error(err_bad_op);
                                  } else
                                      error(err_busy_channel);
                              } else
                                  error(err_bad_channel);
                          } else
                              error(err_bad_func);
                      } else
                          error(err_recv_fault);
                }
                      break;
                case op_clr_function: {
                      uint8_t channel;
                      uint8_t function;
                      if(uart::recv(channel, function)) {
                          if(channel & ac_digital) {
                              if(channel < digital_channel_count) {
                                 //m_analog_out[channel].set_function();
                              } else
                                  error(err_bad_channel);
                          } else
                          if(channel & ac_analog) {
                              if(channel < analog_output_count) {
                                  //m_analog_out[channel].set_function();
                              } else
                                  error(err_bad_channel);
                          } else
                              error(err_bad_func);
                      } else
                          error(err_recv_fault);
                }
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
              if(m_ready_bit) {
                  acknowledge();
              } else
                  recover();
          }
      }
      while(1);
}

void  device::sync() noexcept
{
      if(m_run_bit) {
          if(m_reset_bit) {
              m_reset_bit = 0;
          }
          for(auto iter = std::addressof(m_digital[0]); iter <= std::addressof(m_digital[digital_channel_count]); iter++) {
              iter->sync(m_phase_ctr);
          }
          for(auto iter = std::addressof(m_analog_in[0]); iter <= std::addressof(m_analog_in[analog_input_count]); iter++) {
              iter->sync(m_phase_ctr);
          }
          for(auto iter = std::addressof(m_analog_out[0]); iter <= std::addressof(m_analog_out[analog_output_count]); iter++) {
              iter->sync(m_phase_ctr);
          }
          m_phase_ctr++;
      }
}
