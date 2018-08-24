#ifndef EVE_UNARY_OP
#define EVE_UNARY_OP \
template<typename P, typename=enable_vector<P>>
#endif

#ifndef EVE_BINARY_OP
#define EVE_BINARY_OP \
template<typename T1, typename T2, \
typename = enable_if_t<is_same_dimension<T1, T2>>>
#endif

#ifndef EVE_SCALAR_OP
#define EVE_SCALAR_OP \
template<typename P, typename T, typename=enable_vector<P>>
#endif
