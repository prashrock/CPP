#ifndef _RAND_GENERATORS_CPP_
#define _RAND_GENERATORS_CPP_
#include <algorithm>      /* std::max                        */
#include <vector>         /* std:vector                      */
#include <random>         /* std::default_random_engine      */
#include <cstdlib>        /* srand, rand                     */
#include <sys/time.h>     /* gettimeofday()                  */
#include <unistd.h>       /* getpid()                        */


/* Include PID + current time for seed initialization        *
 * Look at REDIS getRandomHexChars() implementation to see   *
 * how to generate a random Hex string                       *
 * https://github.com/antirez/redis/blob/current-client-fix/src/util.c */
static inline void init_rand()
{
   struct timeval time;
   gettimeofday(&time, NULL);
   /* Multiply with a prime number                           */
   srand((((time.tv_sec ^ getpid()) * 100003) + time.tv_usec));
}

/* Get a random number in the range [min, max]               *
 * As specified in http://c-faq.com/lib/randrange.html       *
 * implement min+rand()/(RAND_MAX/(max-min+1)+1)             */
static inline int get_rand(unsigned int min, unsigned int max)
{
   unsigned int range = max-min+1; /* range within [min,max] */
   unsigned int scale = (RAND_MAX/range)+1; /* scale rand #s */
   return min + rand()/scale;
}

/* Get a random number in the range [0, limit)               *
 * Not using rand()%limit                                    */
static inline int get_rand(unsigned int limit)
{
   return get_rand(0, limit-1);
}

/* Get a random string of given size. Note: by default the   *
 * random string will contain only alphabets, but this can   *
 * easily be customized by passing a different charset       */
static inline std::string get_rand_str(size_t size,
                                   const std::string chars =
                                   "abcdefghijklmnopqrstuvwxyz"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
{
   std::default_random_engine rand_gen{std::random_device{}()};
   std::string s;
   s.reserve(size);
   const int N = chars.size();
   std::uniform_int_distribution<int> pick(0, N - 1);
   for(size_t i = 0; i < size; ++i) s += chars[pick(rand_gen)];
   return s;
}

/* Given an input integer vector, fill it up with random     *
 * numbers in the range [min, max]                           */
template<typename T = int>
static inline void fill_vector_rand(std::vector<T>& v, int min=0,
                                    int max=RAND_MAX)
{
   for(auto &i : v) i = static_cast<T> (get_rand(min, max));
}
   
#endif //_RAND_GENERATORS_CPP_
