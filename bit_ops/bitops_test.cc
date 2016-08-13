//taskset 0x1 ./bit_ops_test
#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <random>            /* std:default_random_engine    */

#include "print_utils.h"     /* print_table_row, MILLION     */
#include "rand_generator.h"  /* init_rand,fill_vector_rand   */
#include "bit_ops.h"         /* Bit Operations               */
#include "time_api.h"        /*C based time mgmt API         */
using namespace std;
using namespace bit_ops;

const int num_loops = MILLION;

struct reverse_test_t {
   unsigned int n;
   unsigned int exp;
};
const struct reverse_test_t reverse_test[2] =  {
   {0x80000000, 0x1},
   {0x24, 0x24000000},
};
   
static bool __attribute__((noinline)) bit_reverse_test() {
   for(auto tst : reverse_test) {
      auto ans = bitReverse<uint32_t>(tst.n);
      if(ans != tst.exp) {
         std::cout << "Error: Reverse failed for 0x" << std::hex
                   << tst.n << " expected 0x" << tst.exp
                   << "got 0x" << ans << endl;
         std::cout.copyfmt(std::ios(NULL));  /* Restore cout     */
         return false;
      }
      ans = bitReverse<uint32_t>(tst.exp);
      if(ans != tst.n) {
         std::cout << "Error: Reverse failed for 0x" << std::hex
                   << tst.exp << " expected 0x" << tst.n
                   << "got 0x" << ans << endl;
         std::cout.copyfmt(std::ios(NULL)); /* Restore cout  */
         return false;
      }
   }
   return true;
}

static bool __attribute__((noinline)) bit_gray_code_test(int lp=num_loops) {
   for(int i = 1, prev_gray = 0; i <= lp; ++i) {
      auto gray = grayCode(i);
      auto bin =  inverseGrayCode(gray);
      if(i != bin) {
         cout << "Error: Gray code failed for " << i
              << " gray= " << std::hex << gray
              << " and inv_gray= " << bin << endl;
         std::cout.copyfmt(std::ios(NULL)); /* Restore cout  */
         return false;
      }
      else if(std::abs(bitPopCnt(gray)- bitPopCnt(prev_gray)) != 1) {
         cout << "Error: Gray code failed pop_cnt for " << i
              << " gray= " << gray << " and prev_gray " << prev_gray << endl;
         return false;
      }
      prev_gray = gray;
   }
   return true;
}

static bool __attribute__((noinline)) bit_parity_test(int lp=num_loops) {
   for(int i = 0; i < lp; ++i) {
      auto calc_parity = bitParity(i);
      auto exp_parity  = bitPopCnt(i) % 2;
      if(calc_parity != exp_parity) {
         cout << "Error: Parity for " << i << " failed."
              << " Exp " << exp_parity << " got " << calc_parity << endl;
         return false;
      }
   }
   return true;
}

static bool __attribute__((noinline)) bit_misc_test(int lp=num_loops) {
   std::default_random_engine generator( std::random_device{}() );
   std::uniform_int_distribution<int>
      intdistribution(std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::max()); /* [-2^31, 2^31-1]   */
   
   if(avg<long long>(5, 6) != 5) {
      cout << "Error: avg(5, 6) failed" << endl; return false;
   }
   if(isPow2<int>(0) != false   || isPow2<int>(536870911) != false ||
      isPow2<int>(32) != true   || isPow2<int>(1) != true          ||
      isPow2<int>(4096) != true || isPow2<int>(536870912) != true ) {
      cout << "Error: isPow2() failed" << endl; return false;
   }
   for(int i = 0; i < lp; ++i) {
      if(isEven(i) == isOdd(i)) {
         cout << "Error: isEven() or isOdd() failed" << endl; return false;
      }
      else if(isEven(i) != ((i & 1) == 0) ) {
         cout << "Error: isEven() failed" << endl; return false;
      }
   }
   for(int i = 0; i < lp; ++i) {
      auto rand_num = intdistribution(generator);
      unsigned exp_val  = std::abs(rand_num);
      unsigned calc_val = bit_ops::abs(rand_num);
      if(calc_val != exp_val) {
         cout << "Error: abs() failed for " << rand_num
              << " exp=" << exp_val << " got=" << calc_val << endl;
         return false;
      }
   }  
   return true;
}

int main()
{
   init_rand();
   if(bit_reverse_test() == false) {
      cout << "Error: Bit reverse test failed" << endl;
      return -1;
   }
   else if(bit_gray_code_test() == false) {
      cout << "Error: Bit Gray code test failed" << endl;
      return -1;
   }
   else if(bit_parity_test() == false) {
      cout << "Error: Bit Parity test failed" << endl;
      return -1;
   }
   else if(bit_misc_test() == false) {
      cout << "Error: Bit Misc test failed" << endl;
      return -1;
   }
   cout << "Info: All manual test-cases passed" << endl;
   return 0;
}

