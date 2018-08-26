#ifndef EVE_DETAIL_INTERNAL_CONTAINER
#define EVE_DETAIL_INTERNAL_CONTAINER

#include <cassert>
#include <cstddef>
#include <cstdlib>

#include <array>
#include <utility>

namespace eve::detail {

using std::aligned_alloc;
using std::forward;

template<class T, size_t n, size_t alignment=alignof(T)>
class container {
  using array_t = std::array<T, n>;
  array_t* m_data;
public:
  using value_type = T;
  using size_type = typename array_t::size_type;
  using difference_type = typename array_t::difference_type;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;
  using iterator = typename array_t::iterator;
  using const_iterator = typename array_t::const_iterator;
  using reverse_iterator = typename array_t::reverse_iterator;
  using const_reverse_iterator = typename array_t::const_reverse_iterator;

  template<typename... Args>
  container(Args... args)
    :  m_data(reinterpret_cast<array_t*>(aligned_alloc(alignment, n*sizeof(T)))) {
    assert(reinterpret_cast<size_t>(m_data)%alignment == 0);
    new(m_data)array_t{std::forward<T>(args)...};
  }

  ~container() {
    m_data->~array_t();
    free(m_data);
  }

  iterator begin() {return m_data->begin();}
  iterator end() {return m_data->end();}
  const_iterator begin() const {return m_data->cbegin();}
  const_iterator end() const {return m_data->cend();}
  const_iterator cbegin() const {return m_data->cbegin();}
  const_iterator cend() const {return m_data->cend();}

  const T& operator[](size_t pos) const {
    return (*m_data)[pos];
  }

  const T* data() const {return m_data->data();}
  T* data() {return m_data->data();}
};

}

#endif
