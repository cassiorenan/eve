#ifndef EVE_DETAIL_STRUCTURED_BINDINGS_HPP
#define EVE_DETAIL_STRUCTURED_BINDINGS_HPP

#include <cstddef>

#include <tuple>

#include "vector.hpp"
#include "type_traits.hpp"

namespace eve::detail {

template<size_t i, typename T, typename=enable_vector<T>>
auto& get(T& p){return p[i];}
template<size_t i, typename T, typename=enable_vector<T>>
auto& get(const T& p){return p[i];}

} // namespace eve::detail

namespace std {

template<typename T, size_t n, typename Allocator>
struct tuple_size<eve::detail::vector<T, n, Allocator>>{static const size_t value{n};};

template<typename T, size_t i, size_t n, typename Allocator>
struct tuple_element<i, eve::detail::vector<T, n, Allocator>>{using type = const T&;};

} // namespace std

#endif // EVE_DETAIL_STRUCTURED_BINDINGS_HPP
