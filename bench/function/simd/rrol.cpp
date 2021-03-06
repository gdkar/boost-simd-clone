// -------------------------------------------------------------------------------------------------
//                              Copyright 2016 - NumScale SAS
//
//                   Distributed under the Boost Software License, Version 1.0.
//                        See accompanying file LICENSE.txt or copy at
//                            http://www.boost.org/LICENSE_1_0.txt
// -------------------------------------------------------------------------------------------------

#include <simd_bench.hpp>
#include <boost/simd/function/simd/rrol.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/pack.hpp>

namespace nsb = ns::bench;
namespace bs =  boost::simd;
namespace bd =  boost::dispatch;

struct myrrol
{
  template<class T> T operator()(const T & a) const
  {
    using iT =  bd::as_integer_t<T>;
    return bs::rrol(a, iT(1));
  }
};

DEFINE_SIMD_BENCH(simd_rrol, myrrol());

DEFINE_BENCH_MAIN()
{
  nsb::for_each<simd_rrol, NS_BENCH_INTEGRAL_TYPES>(-10, 10);
}
