#ifndef EVE_DETAIL_INTERNAL_AVX_FLOAT_SUB_HPP
#define EVE_DETAIL_INTERNAL_AVX_FLOAT_SUB_HPP

#include <immintrin.h>

#include "core.hpp"

namespace eve::detail::simd {

#ifdef __AVX__

template<>
inline void sub<2, float>(float* a, float* b) {
  static auto mask = _mm_setr_epi32(-1, -1, 0, 0);
  SIMD_OP_MASKED(_mm_maskload_ps, _mm_sub_ps, _mm_maskstore_ps);
}

template<>
inline void sub<3, float>(float* a, float* b) {
  static auto mask = _mm_setr_epi32(-1, -1, -1, 0);
  SIMD_OP_MASKED(_mm_maskload_ps, _mm_sub_ps, _mm_maskstore_ps);
}

#else
#ifdef __SSE__

template<>
inline void sub<2, float>(float* a, float* b) {
  static auto zero = _mm_setzero_ps();
  SIMD_OP_HALF(_mm_loadh_pi, _mm_sub_ps, _mm_storeh_pi);
}

template<>
inline void sub<3, float>(float* a, float* b) {
  sub<2>(a, b);
  a[2] += b[2];
}

#endif // #ifdef __SSE__
#endif // #ifdef __AVX__

#if defined(__SSE__) || defined(__AVX__)

template<> struct has_optimized_sub_t<float> : std::true_type {};

template<>
inline void sub<4, float>(float* a, float* b) {
  SIMD_OP_SIMPLE(_mm_load_ps, _mm_sub_ps, _mm_store_ps);
}

#endif

#ifdef __AVX__

template<>
inline void sub<5, float>(float* a, float* b) {
  auto mask = _mm256_setr_epi32(-1, -1, -1, -1, -1, 0, 0, 0);
  SIMD_OP_MASKED(_mm256_maskload_ps, _mm256_sub_ps, _mm256_maskstore_ps);
}

template<>
inline void sub<6, float>(float* a, float* b) {
  auto mask = _mm256_setr_epi32(-1, -1, -1, -1, -1, -1, 0, 0);
  SIMD_OP_MASKED(_mm256_maskload_ps, _mm256_sub_ps, _mm256_maskstore_ps);
}

template<>
inline void sub<7, float>(float* a, float* b) {
  auto mask = _mm256_setr_epi32(-1, -1, -1, -1, -1, -1, -1, 0);
  SIMD_OP_MASKED(_mm256_maskload_ps, _mm256_sub_ps, _mm256_maskstore_ps);
}

template<>
inline void sub<8, float>(float* a, float* b) {
  SIMD_OP_SIMPLE(_mm256_load_ps, _mm256_sub_ps, _mm256_store_ps);
}

#endif // #ifdef __AVX__

} // namespace eve::detail::simd

#endif // EVE_DETAIL_INTERNAL_AVX_FLOAT_SUB_HPP
