#ifndef borg_command_h
#define borg_command_h
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
#include <stdint.h>

/* requests
   op + argc
*/
constexpr uint8_t  nop = 0;
constexpr uint8_t  op_resume = 8;
constexpr uint8_t  op_get_mode = 16;
constexpr uint8_t  op_set_mode = 24;
constexpr uint8_t  op_get_bit = 32;
constexpr uint8_t  op_set_bit = 40;
constexpr uint8_t  op_clr_bit = 48;
constexpr uint8_t  op_get_analog = 56;
constexpr uint8_t  op_set_analog = 64;
constexpr uint8_t  op_get_register = 72;
constexpr uint8_t  op_set_register = 80;
constexpr uint8_t  op_set_input = 96;
constexpr uint8_t  op_set_output = 104;
constexpr uint8_t  op_set_function = 112;     //<op_set_function> <channel> <function>
constexpr uint8_t  op_clr_function = 120;
constexpr uint8_t  op_wait = 208;             //step with clock input
constexpr uint8_t  op_suspend = 216;
constexpr uint8_t  op_zero = 224;             //zero all outputs
constexpr uint8_t  op_reset = 232;            //reset configuration
constexpr uint8_t  op_halt = 240;             //save configuration and sleep
constexpr uint8_t _op = 248;
constexpr uint8_t _argc = 7;

constexpr uint8_t  at_port = 0;
constexpr uint8_t  at_register = 128;
constexpr uint8_t  ac_digital = 32;
constexpr uint8_t  ac_analog = 64;
constexpr uint8_t _at_class = 96;
constexpr uint8_t _at_index = 31;

constexpr uint8_t  fn_none = 0;
constexpr uint8_t  fn_pulse = 1;
constexpr uint8_t  fn_data = 2;
constexpr uint8_t  fn_soft_pwm = 3;
constexpr uint8_t  fn_soft_spi = 4;
constexpr uint8_t  fn_3_phase = 5;
constexpr uint8_t  fn_4_phase = 6;

constexpr uint8_t  opand(uint8_t op, uint8_t argc) noexcept
{
      return op | (argc & _argc);
}

/* responses
*/
constexpr uint8_t  tag_acknowledge = 255;
constexpr uint8_t  tag_error = 0;
#endif
