//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MIN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MIN_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/simd/if_else.hpp>
#include <boost/simd/function/simd/is_less.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( min_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return if_else(is_less(a1, a0), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( min_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::conformant_tag
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( conformant_tag const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
    #if BOOST_COMP_CLANG || (BOOST_COMP_GNUC <  BOOST_VERSION_NUMBER(5,0,0))
      return bs::min(a0, a1);
    #else
      return if_else(is_nan(a1), a0, bs::min(a0, a1));
    #endif
    }
  };
} } }

#endif
