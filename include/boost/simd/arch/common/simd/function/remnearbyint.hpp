//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REMNEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REMNEARBYINT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/div.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/logical_notand.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/if_minus.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF(rem_
                         , (typename A0, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::tag::nearbyint_
                         , bs::pack_<bd::int_<A0>, X>
                         , bs::pack_<bd::int_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(bd::functor<bs::tag::nearbyint_> const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return if_minus(is_nez(a1), a0, div(round,a0,a1)*a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF(rem_
                         , (typename A0, typename X)
                         , (detail::is_native<X>)
                         , bd::cpu_
                         , bs::tag::nearbyint_
                         , bs::pack_<bd::floating_<A0>, X>
                         , bs::pack_<bd::floating_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( bd::functor<bs::tag::nearbyint_> const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      auto z = is_nez(a1);
      return if_else(logical_and(z, is_eqz(a0)),  a0,
                     if_nan_else(logical_or(is_invalid(a1),is_invalid(a0)) ,
                                 if_nan_else(is_eqz(a1),
                                             if_minus(z, a0, div(nearbyint, a0,a1)*a1)
                                            )
                                )
                    );
                     }
    };

    BOOST_DISPATCH_OVERLOAD_IF(rem_
                           , (typename A0, typename X)
                           , (detail::is_native<X>)
                           , bd::cpu_
                           , bs::fast_tag
                           , bs::tag::nearbyint_
                           , bs::pack_<bd::floating_<A0>, X>
                           , bs::pack_<bd::floating_<A0>, X>
                           )
  {
    BOOST_FORCEINLINE A0 operator()(const fast_tag &
                                   , bd::functor<bs::tag::nearbyint_> const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return fnms(div(nearbyint, a0,a1), a1, a0);
    }
  };
} } }

#endif
