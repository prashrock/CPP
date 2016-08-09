#ifndef _COMPILER_API_CPP_
#define _COMPILER_API_CPP_
#include <type_traits>         /* std::is_same               */

/* Compile time assert to enforce types for certain functions*/
#ifndef STATIC_ASSERT_TYPE_INT_UINT
#define STATIC_ASSERT_TYPE_INT_UINT(MYT)                     \
   static_assert((std::is_same<MYT, unsigned int>::value  || \
                  std::is_same<MYT, uint32_t>::value      || \
                  std::is_same<MYT, int32_t>::value),        \
                 "Error: Only INT/UINT supported.")
#endif
#ifndef STATIC_ASSERT_TYPE_UINT_ULONG
#define STATIC_ASSERT_TYPE_UINT_ULONG(MYT)                   \
   static_assert((std::is_same<MYT, unsigned int>::value  || \
                  std::is_same<MYT, uint32_t>::value      || \
                  std::is_same<MYT, unsigned long>::value || \
                  std::is_same<MYT, uint64_t>::value),       \
                 "Error: Only UINT/ULONG supported.")
#endif
#ifndef STATIC_ASSERT_TYPE_INTEGRAL
#define STATIC_ASSERT_TYPE_INTEGRAL(MYT)                     \
   static_assert(std::is_integral<MYT>::value,               \
                 "Error: Only Integral types supported.")
#endif


/* ---------- Branch Prediction MACRO's ---------- */
#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x)    __builtin_expect(!!(x), 0)

/* --- Mark Var/Fn as used/unused to avoid compiler warning --- */
#define _set_as_used(x) (void)(x)
#define _set_as_unused __attribute__((__unused__))


/* --- SFINAE to enable/disable code at compile time --- */
template <bool, typename T = void>
struct enable_if {};
template <typename T>
struct enable_if<true, T> {typedef T type;};

#endif //_COMPILER_API_CPP_
