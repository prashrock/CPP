#ifndef _BASE64_CPP_
#define _BASE64_CPP_

#include <iostream>          /* std::cout                    */
#include <climits>           /* CHAR_BIT                     */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std:vector                   */
#include <string>            /* std::string                  */
#include <unordered_map>     /* std::unordered_map           */
#include <locale>            /* std::isalnum                 */

/**
 * @file  Base64 encoding
 * @brief Base64 encode and decode
 */

typedef  unsigned char b64_digit_t;
/* Given char buffer size, calculate base64 buffer size      *
 * Each ASCII char  needs 8 bits (log_2(256)= 8)             *
 * Each Base64 char needs 6 bits (log_2(64) = 6)             *
 * \therefore 3N ASCII bytes can represent 4n Base64 chars   *
 * or a general formula is ceil(4n/3) i.e., (4n+2)/3         */
static inline size_t ascii_to_base64_bufsize(size_t n) {
   return ((4 * n) + 2) / 3;
}
static inline size_t base64_to_ascii_bufsize(size_t n) {
   return ((3 * n) + 0) / 4;
}
/** @brief checks if given char is valid base64 char         */
static inline bool is_base64(b64_digit_t c) {
   return (std::isalnum(c) || c == '+' || c == '-');
}
static const std::string
base64_digits = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz"
                "0123456789" "+/";

/* @brief Base64 encoding converts every 4 octets(8 bits)    *
 * into 3 sextets(6bits). Tthe ratio of output:input bits    *
 * is 4:3 (33% overhead). i.e, n octets = ceil(4n/3) sextets *
 * Convenient to represent large ID's (128B UUID) in text    */
std::string base64_encode(const std::string& ascii) {
   const size_t inpsz = ascii.size();
   const size_t outsz = ascii_to_base64_bufsize(inpsz);
   std::string res(outsz, '=');
   
   /* Note: every 3 ASCII chars are mapped to 4 BASE64 chars */
   for(size_t i = 0, o = 0; i < inpsz; ) {
      uint32_t ascii_3B = 0;
      /* Let the compiler decide loop unrolling              */
      for(int j = 0; j < 3; ++j) {
         uint8_t octet = (i < inpsz) ? ascii[i++] : 0;
         ascii_3B = (ascii_3B << 8) | octet;
      }
      /* Update upto 4 output chars in each loop             */
      for(size_t j = 0; j < 4 && o < outsz; ++j) {
         int idx = (ascii_3B >> ((3 - j) * 6)) & 0x3F;
         res[o++] = base64_digits[idx];
      }
   }
   /* Pad with 0, 1 or 2 '=' depends on (inp_size % 3)       */
   for (size_t i = 0; (inpsz % 3) && i < 3-(inpsz % 3); i++) res += '=';
   return res;
}

/* @Brief Base64 decoding. Same logic as encoding but need   *
 * an inverted index to lookup Base64 digits from their ASCII*
 * representation.                                           */
std::string base64_decode(const std::string& b64) {
   size_t inpsz = b64.size();
   for(auto it = b64.rbegin(); it != b64.rend() && *it == '='; ++it, inpsz--);
   const size_t outsz = base64_to_ascii_bufsize(inpsz);
   uint8_t b64_map[1 << (sizeof(char) * CHAR_BIT)];
   std::string res(outsz, 0);
   /* First create a inverted index for base-64 digits       */
   for (size_t i = 0; i < base64_digits.size(); ++i)
      b64_map[(uint8_t)base64_digits[i]] = i;

   /* Note: every 4 BASE64 chars are mapped to 3 ASCII chars */
   for(size_t i = 0, o = 0; i < b64.size(); ) {
      uint32_t b64_4 = 0;
      /* For each base64 char, compute base64 digit (0-63)   *
       * and store all the four digits into one uint32_t     */
      /* Let the compiler decide loop unrolling              */
      for(int j = 0; j < 4; ++j, ++i) {
         b64_4 <<= 6;
         if (is_base64(b64[i]))
            b64_4 |= b64_map[(uint8_t)b64[i]];
      }
      /* b64_4 now contains upto 3 ascii chars, extract them */
      for(size_t j = 0; j < 3 && o < outsz; ++j) {
         int idx  = ((b64_4 >> ((2 - j) * 8)));
         res[o++] = static_cast<char> (idx);
      }
   }
   return res;
}

#endif //_BASE64_CPP_
