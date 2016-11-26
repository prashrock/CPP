//g++-5  -Wall -Werror --std=c++11 -g -o ds_string_ipv4_str_to_uint32 ds_string_ipv4_str_to_uint32.cc

/**
 * @file  Convert IP address from string to unsigned int
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::ios::hex                */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string                  */
#include <cstring>           /* strtok                       */
#include <cerrno>            /* errno                        */
using namespace std;

/* Do not tolerate any other char inbetween or in end of string */
unsigned int ip_stoi(std::string ip) {
   unsigned int num = 0;
   size_t b = 0, e = 0;
   /* Expect to see 4 octets in the input string                */
   for(unsigned int i = 0, byte = 0; i < 4; ++i, byte = 0) {
      e = ip.find_first_of('.', b);
      /* Any octet cannot be greater than 3 numbers (max=255)   */
      //if(e - b + 1 > 4) return 0;
      /* Parse current octet and update byte while parsing octet*/
      for(; b < ip.size() && b < e; ++b) {
         if(ip[b] >= '0' && ip[b] <= '9') {
            byte *= 10;
            byte += ip[b] - '0';
         }
         else return 0;
      }
      b = e + 1;
      if(byte > 255) return 0; /* Each octet should be under 256 */
      num <<= 8;
      num += byte;
   }
   /* If entire ip string is not consumed, then return 0         */
   if(e == std::string::npos)  return num;
   else                        return 0;
}

struct test_vector {
   std::string ip;
   unsigned int exp_num;
};

const struct test_vector testv[11] =  {
   {"127.0.0.1",                     0x7f000001},
   {"127.0.0.0",                     0x7f000000},
   {"110.3.244.53",                  0x6e03f435},
   {"182.118.20.178",                0xb67614b2},
   {"74.125.16.64",                  0x4a7d1040},
   {"74.125.16a.64  ",               0x0       },
   {"1234.123.123.123",              0x0       },
   {"123.123.123.123.123",           0x0       },
   {"nice ip",                       0x0       },
   {"0.0.0.0",                       0x0       },
   {"0.0.0",                         0x0       },
};

int main()
{
   for(auto tst : testv) {
      auto ans = ip_stoi(tst.ip);
      if(ans != tst.exp_num) {
         cout << "Error:ip_stoi failed. Exp "
              << tst.exp_num << " Got " << ans
              << " for "     << tst.ip  << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
