#ifndef borg_traits_h
#define borg_traits_h
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
namespace std {

template<class _Tp, _Tp __v>
struct integral_constant
{
    static   constexpr const _Tp value = __v;
    typedef _Tp value_type;
    typedef integral_constant type;

    public:
    constexpr operator value_type() const noexcept {
          return value;
    }

    constexpr value_type operator()() const noexcept {
          return value;
    }
};

template<class _Tp, _Tp __v>
constexpr const _Tp integral_constant<_Tp, __v>::value;

template<bool __b>
using bool_constant = integral_constant<bool, __b>;

typedef bool_constant<true> true_type;
typedef bool_constant<false> false_type;

/* remove reference
*/
template<class _Tp>
struct remove_reference {
  typedef _Tp type;
};

template<class _Tp>
struct remove_reference<_Tp&> {
  typedef _Tp type;
};

template<class _Tp>
struct remove_reference<_Tp&&> {
  typedef _Tp type;
};

/* is_lvalue_reference
*/
template<class _Tp> struct is_lvalue_reference: public false_type {
};

template<class _Tp> struct is_lvalue_reference<_Tp&>: public true_type {
};

/* is_rvalue_reference
*/
template<class _Tp> struct is_rvalue_reference: public false_type {
};

template<class _Tp> struct is_rvalue_reference<_Tp&&>: public true_type {
};

/* forward()
*/
template<class _Tp>
inline constexpr _Tp&& forward(typename remove_reference<_Tp>::type& __t) noexcept
{
      return static_cast<_Tp&&>(__t);
}

template<class _Tp>
inline constexpr _Tp&& forward(typename remove_reference<_Tp>::type&& __t) noexcept
{
      static_assert(is_lvalue_reference<_Tp>::value == false, "can not forward an rvalue as an lvalue");

      return static_cast<_Tp&&>(__t);
}

/* addressof()
*/
template<class _Tp>
inline constexpr _Tp* addressof(_Tp& __x) noexcept {
      return __builtin_addressof(__x);
}
/*namespace std*/ }
#endif
