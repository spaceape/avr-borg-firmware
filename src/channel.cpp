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
#include "channel.h"

      channel::channel() noexcept:
      m_type(0),
      m_busy(0),
      m_enable(0),
      m_value(nullptr)
{
}

      channel::~channel()
{
}


//       channel::channel() noexcept:
//       m_type(0),
//       m_mode(0),
//       m_input(nullptr),
//       m_output(nullptr),
//       m_period(nullptr),
//       m_phase(nullptr)
// {
// }

//       channel::channel(int8_t type, int8_t mode, unsigned long int pi, unsigned long int po) noexcept:
//       m_type(type),
//       m_mode(mode),
//       m_input(reinterpret_cast<int8_t*>(pi)),
//       m_output(reinterpret_cast<int8_t*>(po)),
//       m_period(nullptr),
//       m_phase(nullptr)
// {
// }
    
//       channel::~channel()
// {
// }

// void  channel::sync() noexcept
// {
// }
