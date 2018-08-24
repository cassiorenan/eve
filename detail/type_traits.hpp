#ifndef EVE_TYPE_TRAITS_HPP
#define EVE_TYPE_TRAITS_HPP

#include <cstddef>

#include <type_traits>

#include "vector.hpp"

namespace eve::detail {

using std::common_type_t;
using std::enable_if_t, std::is_same_v;
using std::true_type, std::false_type;

namespace _t {

template<typename T> struct is_vector : false_type{};
template<typename T, size_t n, typename Allocator>
struct is_vector<vector<T, n, Allocator>> : true_type{};

template<typename T> struct dimension {static const auto value = 0;};
template<typename T, size_t n, typename Allocator>
struct dimension<vector<T, n, Allocator>> {static const auto value = n;};

} // namespace _t

template<typename T>
const bool is_vector = _t::is_vector<T>::value;

template<typename T>
const auto dimension = _t::dimension<T>::value;

template<typename T1, typename T2>
constexpr bool is_same_dimension = is_vector<T1>&&
                                   is_vector<T2>&&
                                   (dimension<T1>)==(dimension<T2>);

template<typename T1, typename T2, typename R = void>
using enable_same_dimension = enable_if_t<is_same_dimension<T1, T2>, R>;
template<typename T, typename R = void>
using enable_vector = enable_if_t<is_vector<T>, R>;
template<typename T>
using value_type = typename T::value_type;
template<typename T1, typename T2>
using common_value_type = common_type_t<value_type<T1>, value_type<T2>>;
template<typename T1, typename T2>
const bool is_same_value_type = is_same_v<value_type<T1>, value_type<T2>>;
template<typename T1, typename T2, typename R = void>
using enable_same_value_type = enable_if_t<is_same_value_type<T1, T2>, R>;
template<typename T1, typename T2, typename R = void>
using enable_same = enable_if_t<is_same_v<T1, T2>, R>;
template<typename T1, typename T2, typename R = void>
using disable_same = enable_if_t<!is_same_v<T1, T2>, R>;

} // namespace eve::detail

#endif // EVE_TYPE_TRAITS_HPP
