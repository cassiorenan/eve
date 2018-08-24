#ifndef EVE_DETAIL_IO_HPP
#define EVE_DETAIL_IO_HPP

#include <algorithm>
#include <iostream>
#include <iterator>

#include "type_traits.hpp"

namespace eve::detail {

using std::copy;
using std::basic_ostream;
using std::ostream_iterator;

template<typename T, typename CharT, typename Traits, typename = enable_vector<T>>
auto& operator<<(basic_ostream<CharT, Traits>& out, const T& p) {
  out << '(';
  copy(p.begin(), p.end()-1,ostream_iterator<value_type<T>>(out, ", "));
  out << *(p.end()-1) << ')';
  return out;
}

} // namespace eve::detail

#endif // EVE_DETAIL_IO_HPP
