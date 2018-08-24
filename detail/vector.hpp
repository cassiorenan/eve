#ifndef EVE_DETAIL_VECTOR_HPP
#define EVE_DETAIL_VECTOR_HPP

#include <cstddef>

#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>
#include <utility>

namespace eve::detail {

using std::generate;
using std::allocator;
using std::common_type_t;
using std::enable_if_t;
using std::forward;

template<typename T, size_t n, typename Allocator=allocator<T>>
class vector {
  static_assert(n>1);
  using data_t = std::vector<T, Allocator>;
  data_t m_data;
public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = typename data_t::size_type;
  using difference_type = typename data_t::difference_type;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = typename data_t::iterator;
  using const_iterator = typename data_t::const_iterator;
  using reverse_iterator = typename data_t::reverse_iterator;
  using const_reverse_iterator = typename data_t::const_reverse_iterator;

  iterator begin() {return m_data.begin();}
  iterator end() {return m_data.end();}
  const_iterator begin() const {return m_data.cbegin();}
  const_iterator end() const {return m_data.cend();}
  const_iterator cbegin() const {return m_data.cbegin();}
  const_iterator cend() const {return m_data.cend();}

  template<typename... Ts, typename = enable_if_t<(sizeof...(Ts)>1)>>
  vector(Ts&&... args)
    :  m_data{forward<Ts>(args)...}
  {}

  vector()
    :  m_data(n)
  {}

  template<typename F>
  vector(const F& generator)
    :  m_data(n) {
    generate(begin(), end(), generator);
  }

  T& operator[](size_t i) noexcept {
    return m_data[i];
  }
  const T& operator[](size_t i) const noexcept {
    return m_data[i];
  }
};

template <typename... Ts> vector(Ts... args) -> vector<common_type_t<Ts...>, sizeof...(Ts)>;

} // namespace eve::detail

#endif // EVE_DETAIL_VECTOR_HPP
