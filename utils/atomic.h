#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#include <cstdint>                /* uint32_t */

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------- Atomic Locks and Barriers ------------------ */
/* Compiler barrier.                                                   *
 * Guarantees that operation reordering does not occur at compile time *
 * for operations directly before and after the barrier.               */
#define compile_mem_barrier() do {\
	asm volatile ("" : : : "memory");\
	} while(0)

/* Insert Multi-Processor lock prefix.                                 *
 * Guarantees that LOAD and STORE operations generated                 *
 * before the barrier occur before LOAD and                            *
 * STORE operations generated after.                                   */
#define MPLOCKED "lock ;" 
#define full_mem_barrier() __sync_synchronize()
//asm volatile(MPLOCKED "addl $0,(%%esp)" : : : "memory")

static inline uint32_t unlocked_cmpxchg(uint32_t *dst, uint32_t old,
                                        uint32_t neww)
{
   volatile uint32_t *ptr = (volatile uint32_t *)dst;
   uint32_t ret;
   
   asm volatile ("cmpxchgl %2, %1"
                 : "=a" (ret), "+m" (*ptr)
                 : "r" (neww), "0" (old)
                 : "memory");
   return ret;
}

static inline uint32_t locked_cmpxchg(uint32_t *dst, uint32_t old,
                                      uint32_t neww)
{
   volatile uint32_t *ptr = (volatile uint32_t *)dst;
   uint32_t ret;

   asm volatile ("lock; cmpxchgl %2, %1"
                 : "=a" (ret), "+m" (*ptr)
                 : "r" (neww), "0" (old)
                 : "memory");
   return ret;
}

#ifdef __cplusplus
}
#endif

#endif //_ATOMIC_H_
