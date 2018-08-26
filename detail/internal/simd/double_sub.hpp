#ifndef EVE_DETAIL_INTERNAL_AVX_DOUBLE_SUB_HPP
#define EVE_DETAIL_INTERNAL_AVX_DOUBLE_SUB_HPP

#include <immintrin.h>

#include "core.hpp"

namespace eve::detail::simd {

#if defined(__SSE2__) || defined(__AVX__)

template<> struct has_optimized_sub_t<double> : std::true_type {};

template<>
inline void sub<2, double>(double* a, const double* b) {
  SIMD_OP_SIMPLE(_mm_load_pd, _mm_sub_pd, _mm_store_pd);
}

#endif

#ifdef __AVX__

template<>
inline void sub<3, double>(double* a, const double* b) {
  auto mask = _mm256_setr_epi64x(-1, -1, -1, 0);
  SIMD_OP_MASKED(_mm256_maskload_pd, _mm256_sub_pd, _mm256_maskstore_pd);
}

template<>
inline void sub<4, double>(double* a, const double* b) {
  SIMD_OP_SIMPLE(_mm256_load_pd, _mm256_sub_pd, _mm256_store_pd);
}

#endif // #ifdef __AVX__

} // namespace eve::detail::simd

#endif // EVE_DETAIL_INTERNAL_AVX_DOUBLE_sub_HPP
