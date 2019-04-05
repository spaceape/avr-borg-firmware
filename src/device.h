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
  uint8_t  m_ready_bit:1;
  uint8_t  m_nothing;
  uint8_t  m_phase_ctr;

  protected:
  class virtual_t
  {
    uint8_t m_value;
    public:
            virtual_t() noexcept;
            ~virtual_t();
            uint8_t get() const noexcept;
            void   set(uint8_t) noexcept;
            uint8_t* get_ptr() noexcept;
  };

  class digital_out_t: public channel
  {
    union {
      struct {
        uint8_t  period;
        uint8_t  phase;
        uint8_t* input;
        pin_t    output;
      } counter;
      char  bytes[32];
    } m_data;
  
    public:
            digital_out_t() noexcept;
            ~digital_out_t();
            bool  setup(device*, uint8_t) noexcept;
            void  sync(unsigned int) noexcept;
  };

  class analog_in_t: public channel
  {
    public:
            analog_in_t() noexcept;
            ~analog_in_t();
            void setup(device*, uint8_t);
            void sync(unsigned int) noexcept;
  };

  class analog_out_t: public channel
  {
    public:
            analog_out_t() noexcept;
            ~analog_out_t();
            bool setup(device*, uint8_t) noexcept;
            void sync(unsigned int) noexcept;
  };

  static constexpr unsigned int virtual_channel_count = 32;
  static constexpr unsigned int digital_channel_count = 4;
  static constexpr unsigned int analog_input_count = 8;
  static constexpr unsigned int analog_output_count = 4;
  
  protected:
  virtual_t     m_virtual[virtual_channel_count];
  digital_out_t m_digital[digital_channel_count];
  analog_in_t   m_analog_in[analog_input_count];
  analog_out_t  m_analog_out[analog_output_count];

  protected:
          port_t*  get_port(uint8_t) noexcept;
          virtual_t*  get_register(uint8_t) noexcept;
          digital_out_t*  get_digital_out(uint8_t) noexcept;
          analog_in_t*  get_analog_in(uint8_t) noexcept;
          analog_out_t*  get_analog_out(uint8_t) noexcept;
          bool  get_io_pin(pin_t&) noexcept;
          bool  acknowledge() noexcept;
          void  recall() noexcept;
          void  reset() noexcept;
          void  restore() noexcept;
          void  save() noexcept;
          bool  error(uint8_t, ...) noexcept;
          void  recover() noexcept;
          void  setup() noexcept;

  public:
          device() noexcept;
          ~device();
          void  loop() noexcept;
          void  sync() noexcept;
};
#endif
