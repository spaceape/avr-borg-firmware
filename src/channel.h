#ifndef borg_channel_h
#define borg_channel_h
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

using  func_type = void(*)(void);

struct channel
{
  uint8_t  m_type;
  uint8_t  m_busy:1;
  uint8_t  m_enable:1;

  protected:
  void*    m_value;

  public:
          channel() noexcept;
          ~channel();
};

// class  channel
// {
//   int8_t    m_type;
//   int8_t    m_mode;
//   int8_t    m_xxx;
//   int8_t    m_xxy;
//   int8_t*   m_input;
//   int8_t*   m_output;
//   int8_t*   m_period;
//   int8_t*   m_phase;
//   func_type m_func;
//   func_type m_sync;

//   protected:
//   public:
//   static constexpr uint8_t typ_undef = 0;
//   static constexpr uint8_t typ_reg = 0x20;
//   static constexpr uint8_t typ_bit = 0x40;
//   static constexpr uint8_t typ_pwm = 0x60;
//   static constexpr uint8_t typ_in  = 0;
//   static constexpr uint8_t typ_out = 0x10;

//   static constexpr uint8_t mode_undef = 0;
//   static constexpr uint8_t mode_enabled = 1;
//   static constexpr uint8_t mode_input = 4;
//   static constexpr uint8_t mode_output = 6;

//   public:
//           channel() noexcept;
//           channel(int8_t, int8_t, unsigned long int = 0, unsigned long int = 0) noexcept;
//           ~channel();
//           void run() noexcept;
//           void reset() noexcept;
//           void pause() noexcept;
//           void stop() noexcept;
//           void sync() noexcept;
// };
#endif
