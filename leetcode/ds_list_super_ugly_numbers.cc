//g++-5 --std=c++11 -Wall -g -o ds_list_super_ugly_numbers ds_list_super_ugly_numbers.cc

/**
 * @file  Super Ugly Number
 * @brief Given an array of primes generate nth multiple
 */

// https://leetcode.com/problems/super-ugly-number/

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;


/**
 * Write a program to find the nth super ugly number.
 * Super ugly numbers are positive numbers whose all prime factors
 * are in the given prime list primes of size k.
 * For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the
 * sequence of the first 12 super ugly numbers given
 * primes = [2, 7, 13, 19] of size 4.
 * Note:
 * (1) 1 is a super ugly number for any given primes.
 * (2) The given numbers in primes are in ascending order.
 * (3) 0 < k . 100, 0 < n . 106, 0 < primes[i] < 1000.
 */


/* Find the nth super ugly number                            */
int nthSuperUglyNumber1(int n, vector<int>& primes) {
   /* To generate all multiples, we need to multiply each    *
    * prime with all multiples of all other primes and       *
    * chosing minimum each time. This can be achieved by     *
    * multiplying each prime with all #s in result vector    *
    * The idx vector is to keep track of this multiplication *
    * for each prime number                                  */
   vector<int> idx(primes.size(), 0);
   vector<int> result(n, std::numeric_limits<int>::max());

   result[0] = 1; /* Result always starts with 1             */
   for(int i = 1; i < n; ++i) {
      /* Current result is the min multiple of prime[j]      *
       * and its last result[idx[j]].                        */
      for(int j = 0; j < (int)primes.size(); ++j)
         result[i] = std::min(result[i], result[idx[j]] * primes[j]);
      /* However, each time a result is chosen there are 2   *
       * ways to arrive at that result a*b = b*a. Therefore  *
       * use another loop to increase idx for both a, b      */
      for(int j = 0; j < (int)primes.size(); ++j)
         if(result[i] == result[idx[j]] * primes[j])
            idx[j]++;
   }
   return result[n-1];
}

/* Find the nth super ugly number. Fuse 2 inner for loops    */
int nthSuperUglyNumber2(int n, vector<int>& primes) {
   vector<int> idx(primes.size(), 0), result(n);
   result[0] = 1; /* Result always starts with 1             */
   for(int i = 1, j_idx = 0; i < n; ++i) {
      result[i] = std::numeric_limits<int>::max();
      for(int j = 0; j < (int)primes.size(); ++j) {
         auto cur_val = primes[j] * result[idx[j]];
         /* Current result is the min multiple of prime[j]   *
          * and its last result[idx[j]].                     */
         if(result[i] > cur_val) {
            result[i] = cur_val;
            j_idx     = j;
         }
         /* Update 2nd prime idx (a * b = b * a)             */
         else if(result[i] == cur_val)
            idx[j]++;
      }
      idx[j_idx]++;
   }
   //for(auto v : result) cout << v << ","; cout << endl;
   return result[n-1];
}

int main()
{
   int ans1, ans2, exp, n;
   vector<int> primes;

   primes = {2,3,5}; n = 1; exp = 1;
   ans1 = nthSuperUglyNumber1(n, primes);
   ans2 = nthSuperUglyNumber2(n, primes);
   if(ans1 != exp) goto Errmain1;
   if(ans2 != exp) goto Errmain2;

   primes = {2, 7, 13, 19}; n = 12; exp = 32;
   ans1 = nthSuperUglyNumber1(n, primes);
   ans2 = nthSuperUglyNumber2(n, primes);
   if(ans1 != exp) goto Errmain1;
   if(ans2 != exp) goto Errmain2;
   cout << "All test-cases passed." << endl;
   return 0;
 Errmain1:
   cout << "Error: Super Ugly Number (non-opt) mode failed for - ";
   for(auto val: primes) cout << val << ", "; cout << endl;
   cout << "Expected = " << exp << " Got = " << ans1 << endl;
   return -1;
 Errmain2:
   cout << "Error: Super Ugly Number (opt) mode failed for - ";
   for(auto val: primes) cout << val << ", "; cout << endl;
   cout << "Expected = " << exp << " Got = " << ans2 << endl;
   return -1;
}
