#ifndef borg_mmio_h
#define borg_mmio_h
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
#include <avr/io.h>
#include <avr/interrupt.h>

/* determine gpio_min and gpio_max
 * NOTE: not necesarily the best way to do it
*/
#if defined DDRA
static constexpr unsigned long int gpio_min = 0;
#elif defined DDRB
static constexpr unsigned long int gpio_min = 1;
#else
    #error "Cannot determine min GPIO port"
#endif

#if defined PINH
static constexpr unsigned long int gpio_max = 7;
#elif defined PING
static constexpr unsigned long int gpio_max = 6;
#elif defined PINF
static constexpr unsigned long int gpio_max = 5;
#elif defined PINE
static constexpr unsigned long int gpio_max = 4;
#elif defined PIND
static constexpr unsigned long int gpio_max = 3;
#elif defined PINC
static constexpr unsigned long int gpio_max = 2;
#elif defined PINB
static constexpr unsigned long int gpio_max = 1;
#else
static constexpr unsigned long int gpio_max = 7;
#endif

/*bits each port has*/
static constexpr unsigned long int gpio_port_size = 8;

/*bits all present ports have in total*/
static constexpr unsigned long int gpio_size = gpio_port_size * (gpio_max - gpio_min);

using  port_t = volatile uint8_t;

struct pin_t
{
  port_t*  m_port;
  uint8_t  m_bit;
  uint8_t  m_aux;
};

namespace mmio {

void init() noexcept;

constexpr uint8_t get_gpio_min() noexcept {
      return gpio_min;
}

constexpr uint8_t get_gpio_max() noexcept {
      return gpio_max;
}

port_t& get_gpio_pin(uint8_t) noexcept;
port_t& get_gpio_port(uint8_t) noexcept;
port_t& get_gpio_mode(uint8_t) noexcept;
void drop() noexcept;

/*namespace mmio*/ }
#endif
