#ifndef borg_device_h
#define borg_device_h
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
#include <firmware.h>
#include "channel.h"

class device
{
  uint8_t  m_run_bit:1;
  uint8_t  m_wait_bit:1;
  uint8_t  m_reset_bit:1;
  uint8_t  m_error_bit:1;
  uint8_t  m_nothing;
  uint16_t m_phase_ctr;

  protected:
  class virtual_t: public channel
  {
    union {
      uint8_t v[12];
    } m_data;
    public:
          virtual_t() noexcept;
          ~virtual_t();
  };

  class digital_out_t: public channel
  {
    union {
      struct {
        uint8_t*  m_period;
        uint8_t*  m_phase;
      } x;
      uint8_t v[12];
    } m_data;

    protected:
    static  void  f_sync_null(digital_out_t*) noexcept;
    static  void  f_sync_clock(digital_out_t*) noexcept;
    static  void  f_sync_data(digital_out_t*) noexcept;
    static  void  f_sync_spi(digital_out_t*) noexcept;
    static  void  f_sync_motor(digital_out_t*) noexcept;
    static  void  f_sync_soft_pwm(digital_out_t*) noexcept;

    public:
            digital_out_t() noexcept;
            ~digital_out_t();
  };

  class analog_in_t: public channel
  {
    union {
      uint8_t v[12];
    } m_data;
    public:
          analog_in_t() noexcept;
          ~analog_in_t();
  };

  class analog_out_t: public channel
  {
    union {
      uint8_t v[12];
    } m_data;
    public:
          analog_out_t() noexcept;
          ~analog_out_t();
  };

  static constexpr unsigned int phase_min = 0;
  static constexpr unsigned int phase_max = 256;
  static constexpr unsigned int phase_step = 32;

  protected:
  virtual_t     m_virtual[16];
  digital_out_t m_digital[4];
  analog_in_t   m_analog_in[8];
  analog_out_t  m_analog_out[4];

  protected:
          uint8_t get_channel(uint8_t) noexcept;
          uint8_t get_register(uint8_t) noexcept;
          bool  acknowledge() noexcept;
          int   emit(uint8_t) noexcept;
          int   emit(uint8_t*, unsigned long int) noexcept;
          bool  expect(uint8_t, uint8_t, uint8_t, uint8_t) noexcept;
          bool  expect() noexcept;
          void  recall() noexcept;
          void  reset() noexcept;
          void  restore() noexcept;
          void  save() noexcept;
          void  error(uint8_t, ...) noexcept;
          void  recover() noexcept;
          void  setup() noexcept;

  public:
          device() noexcept;
          ~device();
          void  loop() noexcept;
          void  sync() noexcept;
};
#endif
