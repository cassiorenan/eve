#ifndef EVE_DETAIL_INTERNAL_AVX_CORE_HPP
#define EVE_DETAIL_INTERNAL_AVX_CORE_HPP

#include <type_traits>

#define SIMD_BASIC_OP(op, func) \
template<size_t length, typename T>\
void op(T* a, const T* b) {\
  const size_t pack_size = alignment/sizeof(T);\
  size_t i = 0;\
  for(;i<(length-pack_size);i+=pack_size) {\
      op<pack_size>(a+i, b+i);\
  }\
  if constexpr (length%pack_size > 1) {\
    op<length%pack_size>(a+i, b+i);\
  } else if constexpr (length%pack_size == 1) {\
    func((a+i), (b+i));\
  }\
}

namespace eve::detail::simd {
  using std::remove_cv_t;
  using std::remove_reference_t;
  template<typename T>
  using noq = remove_reference_t<remove_cv_t<T>>;
#  ifdef __AVX__
  inline const size_t alignment = 32;
#  else
#    ifdef __SSE2__
  inline const size_t alignment = 16;
#    else
  inline const size_t alignment = alignof(double);
#    endif
#  endif

  template<typename T> struct has_optimized_add_t : std::false_type {};
  template<typename T> inline const bool has_optimized_add = has_optimized_add_t<noq<T>>::value;

  template<typename T> struct has_optimized_sub_t : std::false_type {};
  template<typename T> inline const bool has_optimized_sub = has_optimized_sub_t<T>::value;

  template<typename T> constexpr void basic_add(T* a, T* b) {*a += *b;}
  template<typename T> constexpr void basic_sub(T* a, T* b) {*a -= *b;}
  SIMD_BASIC_OP(add, basic_add)
  SIMD_BASIC_OP(sub, basic_sub)
}

#define SIMD_OP_SIMPLE(load, operation, store) \
auto va = load(a);\
auto vb = load(b);\
auto vr = operation(va, vb);\
store(a, vr)

#define SIMD_OP_MASKED(load, operation, store) \
auto va = load(a, mask);\
auto vb = load(b, mask);\
auto vr = operation(va, vb);\
store(a, mask, vr)

#define SIMD_OP_HALF(load, operation, store) \
auto va = load(zero, reinterpret_cast<__m64*>(a));\
auto vb = load(zero, reinterpret_cast<const __m64*>(b));\
auto vr = operation(va, vb);\
store(reinterpret_cast<__m64*>(a), vr)

#endif
