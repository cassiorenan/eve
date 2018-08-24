#ifndef EVE_DETAIL_FUNCTIONS_HPP
#define EVE_DETAIL_FUNCTIONS_HPP

#include <cmath>

#include <numeric>
#include <utility>

#include "operators.hpp"
#include "type_traits.hpp"

#include "internal/op.hpp"

namespace eve::detail {

using std::inner_product;
using std::move;

EVE_BINARY_OP
auto dot_product(const T1& a, const T2& b) {
  return inner_product(a.cbegin(), a.cend(), b.cbegin(), common_value_type<T1, T2>{0});
}

EVE_UNARY_OP
auto square_length(const P& p) {
  return dot_product(p, p);
}

EVE_UNARY_OP
auto length(const P& p) {
  return sqrt(square_length(p));
}

EVE_BINARY_OP
auto distance(const T1& a, const T2& b) {
  return length(a-b);
}

EVE_BINARY_OP
auto square_distance(const T1& a, const T2& b) {
  return square_length(a-b);
}

EVE_UNARY_OP
P normalize(P p) {return move(p/=length(p));}

} // namespace eve::detail

#include "internal/op_undef.hpp"

#endif
