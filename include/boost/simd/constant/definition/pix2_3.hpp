//==================================================================================================
/*!
  @file

  @copyright 2012-2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_PIX2_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_PIX2_3_HPP_INCLUDED

#include <boost/simd/detail/brigand.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/dispatch/function/make_callable.hpp>
#include <boost/dispatch/hierarchy/functions.hpp>
#include <boost/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct pix2_3_ : boost::dispatch::constant_value_<pix2_3_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,pix2_3_,boost::dispatch::constant_value_<pix2_3_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0X31885A30, 0X3BC3198A2E037073LL//3B498A2E03707345LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag,pix2_3_);
  }

  namespace functional
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pix2_3_,pix2_3);
  }

  template<typename T> BOOST_FORCEINLINE auto Pix2_3() BOOST_NOEXCEPT
  -> decltype(functional::pix2_3( boost::dispatch::as_<T>{}))
  {
    return functional::pix2_3( boost::dispatch::as_<T>{} );
  }
} }

#endif
