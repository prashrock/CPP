#ifndef _PRINT_UTILS_CPP_
#define _PRINT_UTILS_CPP_

#include <iostream>       /* std::cout               */
#include <iomanip>        /* std::setw               */
#include <algorithm>      /* std::vector             */
using namespace std;

#ifndef MILLION
#define MILLION (1000000)          /* 10^6           */
#endif
#ifndef BILLION
#define BILLION (1000000000ULL)    /* 10^9           */
#endif

/* Nice print a table row by row                     */
template<typename T>
static inline void
print_table_row(std::string name, const std::vector<T>& v,
                int str_size=20, int col_width=3) {
   std::cout << std::left << std::setw(str_size) << std::setfill(' ')
             << name;
   std::cout << ": ";
   for(auto i : v)
      std::cout << std::right << std::setw(col_width) << i << " ";
   std::cout << std::endl;
}

#endif //_PRINT_UTILS_CPP_
