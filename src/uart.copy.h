#ifndef borg_uart_h
#define borg_uart_h
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

#ifdef F_CPU
  #if !(F_CPU)
  #  error "F_CPU must be a constant value"
  #endif
#else
#  error "setbaud.h requires F_CPU to be defined"
#endif

#ifdef BAUD
  #if !(BAUD)
  #  error "BAUD must be a constant value"
  #endif
#else
  #define BAUD 9600
#endif

namespace uart {

constexpr uint16_t get_baud_delay(uint32_t baud = BAUD, bool use_2x = true) {
      if(baud > F_CPU / 1048576) {
          if(baud < F_CPU / 16) {
              if(use_2x) {
                  return F_CPU / (8 * baud) - 1;
              } else
                  return F_CPU / (16 * baud) - 1;
          }
      }
      return 0;
}

constexpr uint8_t get_UBRR_l(uint32_t baud = BAUD, bool use_2x = true) {
      return get_baud_delay(baud, use_2x) & 255;
}

constexpr uint8_t get_UBRR_h(uint32_t baud = BAUD, bool use_2x = true) {
      return (get_baud_delay(baud, use_2x) >> 8) & 255;
}

constexpr unsigned long int get_baud_timeout(uint32_t baud = BAUD, bool use_2x = true) {
      //return get_baud_delay(baud, use_2x) * 8;
      return 256;
}

constexpr unsigned long int recv_timeout_min = 1;
constexpr unsigned long int recv_timeout_default = get_baud_timeout();

void  init(uint32_t = BAUD, bool = USE_2X) noexcept;

bool  recv(uint8_t*) noexcept;
bool  recv(uint8_t&) noexcept;
bool  recv_wait(uint8_t*, unsigned long int) noexcept;
bool  recv_wait(uint8_t&, unsigned long int) noexcept;

inline  bool  recv_le(uint8_t* value) noexcept {
        return recv_wait(value, recv_timeout_default);
}

inline  bool  recv_le(uint8_t& value) noexcept {
        return recv_wait(value, recv_timeout_default);
}

template<typename Xt>
inline  bool  recv_le(Xt* value) noexcept {
        uint8_t* data = reinterpret_cast<uint8_t*>(value);
        uint8_t* last = data + sizeof(Xt);
        while(data < last) {
            if(recv_le(data) == false) {
                return false;
            }
            data++;
        }
        return true;
}

template<typename Xt>
inline  bool  recv_le(Xt& value) noexcept {
        return recv_le(std::addressof(value));
}

template<typename Xt, typename... Args>
inline  bool  recv_le(Xt& value, Args&&... args) noexcept {
        return recv_le(value) && recv_le(std::forward<Args>(args)...);
}

inline  bool  recv_be(uint8_t* value) noexcept {
        return recv_wait(value, recv_timeout_default);
}

inline  bool  recv_be(uint8_t& value) noexcept {
        return recv_wait(value, recv_timeout_default);
}

template<typename Xt>
inline  bool  recv_be(Xt* value) noexcept {
        uint8_t* last = reinterpret_cast<uint8_t*>(value) - 1;
        uint8_t* data = last + sizeof(Xt);
        while(data > last) {
            if(recv_be(data) == false) {
                return false;
            }
            data--;
        }
        return true;
}

template<typename Xt>
inline  bool  recv_be(Xt& value) noexcept {
        return recv_be(std::addressof(value));
}

template<typename Xt, typename... Args>
inline  bool  recv_be(Xt& value, Args&&... args) noexcept {
        return recv_be(value) && recv_be(std::forward<Args>(args)...);
}

inline  bool  get_uint8(uint8_t& value) noexcept {
        return recv_le(value);
}

inline  bool  get_uint16(uint16_t& value) noexcept {
        return recv_le(value);
}

inline  bool  get_uint32(uint16_t& value) noexcept {
        return recv_le(value);
}

inline  bool  get_float(float& value) noexcept {
        return recv_le(value);
}

template<typename Xt, typename... Args>
inline  bool  recv(Xt* value, Args&&... args) noexcept {
        return recv_le(value) && recv_le(std::forward<Args>(args)...);
}

template<typename Xt, typename... Args>
inline  bool  recv(Xt& value, Args&&... args) noexcept {
        return recv_le(value) && recv_le(std::forward<Args>(args)...);
}

void  send(uint8_t) noexcept;

template<typename Xt>
void  send(Xt&) noexcept {
}

template<typename Xt>
void  send(const Xt&) noexcept {
}

template<typename Xt, typename... Args>
void  send(Xt& value, Args&&... args) noexcept {
      send(value);
      send(std::forward<Args>(args)...);
}

template<typename Xt, typename... Args>
void  send(const Xt& value, Args&&... args) noexcept {
      send(value);
      send(std::forward<Args>(args)...);
}

void  drop() noexcept;

/*namespace uart*/ }
#endif
