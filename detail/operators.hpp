#ifndef EVE_DETAIL_OPERATORS_HPP
#define EVE_DETAIL_OPERATORS_HPP

#include <algorithm>
#include <utility>

#include "type_traits.hpp"

#include "internal/op.hpp"
#include "internal/simd/intel.hpp"

namespace eve::detail {

using std::equal;
using std::for_each;
using std::move;

EVE_BINARY_OP
T1& operator+=(T1& lhs, const T2& rhs) noexcept {
  if constexpr (simd::has_optimized_add<value_type<T1>> && is_same_value_type<T1, T2>) {
    simd::add<dimension<T1>>(lhs.data(), rhs.data());
  } else {
    auto b = rhs.begin();
    for(auto a = lhs.begin(); a != lhs.end(); ++a, ++b) {
      *a += *b;
    }
  }
  return lhs;
}

EVE_BINARY_OP
auto& operator-=(T1& lhs, const T2& rhs) noexcept {
  if constexpr (simd::has_optimized_add<value_type<T1>> && is_same_value_type<T1, T2>) {
    simd::add<dimension<T1>>(lhs.data(), rhs.data());
  } else {
    auto b = rhs.begin();
    for(auto a = lhs.begin(); a != lhs.end(); ++a, ++b) {
      *a -= *b;
    }
  }
  return lhs;
}

EVE_SCALAR_OP
auto& operator/=(P& lhs, const T& val) noexcept {
  for_each(lhs.begin(), lhs.end(), [&val](auto& v){
    v /= val;
  });
  return lhs;
}

EVE_SCALAR_OP
auto& operator*=(P& lhs, const T& val) noexcept {
  for_each(lhs.begin(), lhs.end(), [&val](auto& v){
    v *= val;
  });
  return lhs;
}

EVE_UNARY_OP
P operator-(P p) {
  return move(p*=-1);
}

EVE_BINARY_OP
bool operator==(const T1& a, const T2& b) {
  return equal(a.begin(), a.end(), b.begin());
}

EVE_BINARY_OP
enable_if_t<is_same_v<value_type<T1>, common_value_type<T1, T2>>, T1>
operator+(T1 a, const T2& b) {return move(a+=b);}

EVE_BINARY_OP
enable_if_t<!is_same_v<value_type<T1>, common_value_type<T1, T2>>, T2>
operator+(const T1& a, T2 b) {return move(b+=a);}

EVE_BINARY_OP
enable_if_t<is_same_v<value_type<T1>, common_value_type<T1, T2>>, T1>
operator-(T1 a, const T2& b) {return move(a-=b);}

EVE_BINARY_OP
enable_if_t<!is_same_v<value_type<T1>, common_value_type<T1, T2>>, T2>
operator-(const T1& a, T2 b) {return move(b-=a);}

}

#include "internal/op_undef.hpp"

#endif
