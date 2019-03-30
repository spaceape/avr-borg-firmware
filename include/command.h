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
*/
constexpr uint8_t  nop = 0;
constexpr uint8_t  op_resume = 8;
constexpr uint8_t  op_set_mode = 16;
constexpr uint8_t  op_get_bit = 24;
constexpr uint8_t  op_set_bit = 32;
constexpr uint8_t  op_clr_bit = 40;
constexpr uint8_t  op_get_analog = 48;
constexpr uint8_t  op_set_analog = 56;
constexpr uint8_t  op_wait = 216;        //step with clock input
constexpr uint8_t  op_suspend = 224;
constexpr uint8_t  op_zero = 232;        //zero all outputs
constexpr uint8_t  op_reset = 240;       //reset configuration
constexpr uint8_t  op_halt = 248;        //save configuration and sleep
constexpr uint8_t _op = 248;
constexpr uint8_t _index = 7;

/* responses
*/
constexpr uint8_t  tag_error = 0;
constexpr uint8_t  tag_acknowledge = 170;
#endif
