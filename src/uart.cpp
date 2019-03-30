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
#include <uart.h>
#include <avr/io.h>

namespace uart {

void  init(uint32_t baud, bool use_2x) noexcept
{
      UBRR0L = uart::get_UBRR_l(baud, use_2x);
      UBRR0H = uart::get_UBRR_h(baud, use_2x);
      if(use_2x) {
          UCSR0A |=_BV(U2X0);
      } else
          UCSR0A &=~(_BV(U2X0));
      UCSR0C =_BV(UCSZ01) |_BV(UCSZ00); /* 8-bit data */
      UCSR0B =_BV(RXEN0) |_BV(TXEN0);   /* Enable RX and TX */
}

void  send(uint8_t value) noexcept
{
      loop_until_bit_is_set(UCSR0A, UDRE0);
      UDR0 = value;
    //loop_until_bit_is_set(UCSR0A, TXC0); /* Wait until transmission ready. */
}

uint8_t recv() noexcept
{
      loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
      return UDR0;
}

bool recv(uint8_t* value, unsigned long int timeout) noexcept
{
      while(timeout) {
          if(bit_is_set(UCSR0A, RXC0)) {
              *value = UDR0;
              return true;
          }
          timeout--;
      }
      return false;
}

bool recv(uint8_t& value, unsigned long int timeout) noexcept
{
      while(timeout) {
          if(bit_is_set(UCSR0A, RXC0)) {
              value = UDR0;
              return true;
          }
          timeout--;
      }
      return false;
}

void  drop() noexcept
{
}
/*namespace uart*/ }
