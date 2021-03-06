#ifndef _SUBSTRING_UTILS_CPP_
#define _SUBSTRING_UTILS_CPP_

/**
 * @file  Substring
 * @brief Substring functions
 */
#include <vector>         /* std:vector                      */
#include <algorithm>      /* std::max                        */
#include "hash_fns.h"     /* rolling_hash()                  */

/**
 * Naive Substring method:                                   *
 * @param text                                               *
 *   Text in which to search for pattern (haystack)          *
 * @param pat                                                *
 *   Pattern to search for (needle)                          *
 * @return                                                   *
 *   0-based pattern start idx  or -1 if pattern not found   *
 * For every position in text, consider it as a starting     *
 * position for pattern and see if there is a match.         *
 * Best for : Short text and pattern                         *
 * Worst Case Time Complexity = O(NM) (Typical = O(1.1N))    *
 * Space Complexity           = O(1)                         */
template<typename T=std::string>
static inline int substring_brute(T text, T pat) {
   if(text.empty() || pat.empty()) return -1;
   for(size_t i = 0, j = 0; i <= (text.size() - pat.size()); ++i) {
      for(j = 0; j < pat.size() && i + j < text.size(); ++j) 
         if(text[i + j] != pat[j]) break;
      
      if(j == pat.size()) return i; /* Return on 1st match   */
   }
   return -1;
}

/**
 * Optimized Naive method:                                   *
 * @param text                                               *
 *   Text in which to search for pattern (haystack)          *
 * @param pat                                                *
 *   Pattern to search for (needle)                          *
 * @return                                                   *
 *   0-based pattern start idx  or -1 if pattern not found   *
 * Use one for-loop to iterate over the text and backup text *
 * explicitly everytime there is a mismatch (rewind pattern  *
 * as well).                                                 *
 * Best for : Short text and pattern                         *
 * Worst Case Time Complexity = O(NM) (Typical = O(1.1N))    *
 * Space Complexity           = O(1)                         */
template<typename T=std::string>
static inline int substring_opt(T text, T pat)
{
   size_t i, j;
   if(text.empty() || pat.empty()) return -1;
   /* Break loop when either text or pat is fully traversed  */
   for(i = 0, j = 0; i < text.size() && j < pat.size(); ++i) {
      if(text[i] == pat[j]) j++;
      /* if mismatch, backtrack text by j and reset pat      */
      else {
         i -= j;
         j  = 0;
      }
   }
   if(j == pat.size())   return (i - pat.size());
   else                  return -1;
}


/**
 * Knuth Morris Pratt Discrete Finite State Machine Algo:    *
 * @param pat                                                *
 *   Pattern to search for (needle)                          *
 * @param lps                                                *
 *   Int arr = Longest Proper Prefix which is also a suffix  *
 * @param n                                                  *
 *   Pattern length                                          *
 * @return                                                   *
 *   0 on success and -1 on failure                          *
 * DFA preprocessing involves constructing an auxiliary array*
 * lps[pattern_size]. For each sub-pattern pat[0 - i] where  *
 * i = 0 to m-1:                                             *
 * lps[i] = ln of longest matching proper prefix which is    *
 * also a suffix of the sub-pattern pat[0..i].               *
 * There are three cases handled below:                      *
 * Case 1 : Match                                            *
 * - If cur prefix and i'th char match, lps_len++ and i++    *
 * Case 2 : No Match + LPS length == 0                       *
 * - LPS empty and pat[i] != pat[0], lps[i] = 0 and i++      *
 * Case 3 : No Match + LPS length != 0                       *
 * - lps_len > 0 && pat[i] != pat[0], point lps_len to prev  *
 * lps char (lps_len = lps[lps_len - 1] && don't increment i *
 * i.e., stay in case 3, till lps_len = 0 (i.e., case 2)     */
template<typename T=std::string>
static inline int kmp_prefix_dfa(T pat, int lps[], int n) {
   /* length of previous longest prefix that is also suffix  */
   int lps_len = 0;
   lps[0] = 0;   /* single char string = no proper prefix    */
   for(int i = 1; i < n;) {
      /* Case 1: Cur Prefix and the ith char match, move fwd */
      if(pat[lps_len] == pat[i]) lps[i++] = ++lps_len;
      /* Case 2: No match and the lps_length is 0, move fwd  */
      else if(lps_len == 0)      lps[i++] = 0;
      /* Case 3: No match and lps_length is non-zero (stay)  */
      else                       lps_len  = lps[lps_len - 1];
   }
   return 0;
}


/* Dump the pattern string and LPS table from a pattern str  */
void kmp_lps_dump_helper(const std::string pattern_str) {
   const int N = pattern_str.size();
   std::vector<char> pat(pattern_str.begin(), pattern_str.end());
   std::vector<int> val(N, 0);
   print_table_row<char>("pattern", pat);
   kmp_prefix_dfa(pattern_str, &val[0], N);
   print_table_row<int>("KMP Result", val);
}
	
/**
 * Knuth Morris Pratt Search Algo:                           *
 * @param text                                               *
 *   Text in which to search for pattern (haystack)          *
 * @param pat                                                *
 *   Pattern to search for (needle)                          *
 * @return                                                   *
 *   0-based pattern start idx  or -1 if pattern not found   *
 * Build pattern prefix table - Longest proper prefix which  *
 * is also a suffix                                          *
 * Best for : Long text + Pattern with small radix and lot   *
 * of repetitions (example: DNA sequence)                    *
 * Worst Case Time Complexity = O(3N) (Typical = O(1.1N))    *
 * Space Complexity           = O(M)                         *
 * Advantages:                                               *
 * - No text backtrack needed (supports input text stream)   */
template<typename T=std::string>
static inline int substring_kmp(T text, T pat) {
   size_t M = pat.size();
   /* LPS = store the DFA result of longest prefix match     */
   std::vector<int> lps(M);
   size_t i, j;
   if(text.empty() || pat.empty()) return -1;
   kmp_prefix_dfa(pat, &lps[0], M);
   for(i = 0, j = 0; i < text.size() && j < M; ++i) {
      /* Backtrack pat if required but not the text          */
      while (j > 0 && text[i] != pat[j])
         j = lps[j - 1];		
      if(text[i] == pat[j]) j++;
   }
   if(j == M)   return (i - M);
   else         return -1;
}

/**
 * Boyer-Moore Substring Match Algo:                         *
 * @param text                                               *
 *   Text in which to search for pattern (haystack)          *
 * @param pattern                                            *
 *   Pattern to search for (needle)                          *
 * @return                                                   *
 *   0-based pattern start idx  or -1 if pattern not found   *
 * Scan pattern chars from right to left. Skip as many as M  *
 * text chars when finding one not in the pattern            *
 * Best for :Long pattern resembling natural text(eg:English)*
 * Worst Case Time Complexity = O(MN) (Typical = O(N/M))     *
 * Space Complexity           = O(R) where R = Radix         *
 * Note - below impl assumes Radix is 256 (Extended ASCII    *
 * char sequence).                                           *
 * Note - GNU grep uses Boyer Moore with unrolled inner loop *
 * Note2- Implementation based on Robert Sedgewick lectures@ *
 * algs4.cs.princeton.edu/lectures/53SubstringSearch.pdf     */
template<typename T=std::string, size_t R=256>
static inline int substring_boyer_moore(T text, T pat) {
   const auto  N = text.size(), M = pat.size();
   if(text.empty() || pat.empty()) return -1;
   std::vector<int> radix(R, -1);
   
   /* Pre-processing - pre-compute the rightmost occurence  *
    * of each character 'c' in the pattern                  */
   for(size_t i = 0; i < M; ++i) {
      unsigned pos = static_cast<char>(pat[i]);
      radix[pos] = i; /*Only store last occur of character  */
   }
	
   /* Actual Boyer-Moore String Search Algorithm            */
   int skip = 0; /* How many char to skip matching in text  */
   /* Use condition <= to facilitate text == pattern case   */
   for(size_t i = 0; i <= (N - M); i += skip) {
      skip = 0;
      for(int j = M - 1; j >= 0; j--) {
         if(text[i+j] != pat[j]) {
            skip = std::max(1, j - radix[pat[j]]);
            break;
         }
      }
      if(skip == 0) return i;
   }
   return -1;
}

/**
 * Rabin-Karp Substring Match Algo(Monte-Carlo approach):    *
 * @param text                                               *
 *   Text in which to search for pattern (haystack)          *
 * @param pattern                                            *
 *   Pattern to search for (needle)                          *
 * @return                                                   *
 *   0-based pattern start idx  or -1 if pattern not found   *
 * Modular Hashing approach. Compute hash of pattern[0, M-1] *
 * For each i, compute hash of text[i, M+i-1].               *
 * If pattern_hash==text_substring_hash --> potential match. *
 * With Monte-Carlo approach, no validation done, i.e.,      *
 * potential match substrings are not compared (validated),  *
 * just assume very low probability of hash collision, i.e., *
 * (tolerate false-positives)                                *
 * Worst Case Time Complexity = O(7N) (Typical = O(7N))      *
 * Space Complexity           = O(1)                         */
template<typename T=std::string, size_t R=256,
	unsigned long prime=5915587277>
static inline int substring_rabin_karp(T text, T pattern) {
   if(text.empty() || pattern.empty()) return -1;
   size_t M = pattern.size();
   unsigned long RM1 = 1; /* R^(M-1) % prime                */
   unsigned long pattern_hash = rolling_hash(pattern, R, prime);
   unsigned long hash = rolling_hash(text.substr(0, M), R, prime);
	
   /* Precompute  R^(M-1) % prime                           */
   for(size_t i = 1; i < M; ++i)
      RM1 = (R * RM1) % prime;

   /* Actual Rabin-Karp String Search Algorithm             */
   if(pattern_hash == hash)     return 0; /* Full/1st match */
   for(size_t i = M; i < text.size(); ++i) {
      /* Remove left-most character from rolling hash      */
      hash = (hash + prime - (RM1 * text[i-M] % prime)) % prime;
      /* Add right-most character to the rolling hash      */
      hash = ((hash * R) + text[i]) % prime;
      /* Monte-Carlo version. Don't verify substrings      */
      if(pattern_hash == hash)
         return (i - M + 1);
   }
   return -1;
}

template<typename T=std::string>
static inline int substring_stil_find(T text, T pat) {
   if(text.empty() || pat.empty()) return -1;
   auto ret = text.find(pat);
   if(ret == std::string::npos)    return -1;
   else                            return static_cast<int> (ret);
}
#endif //_SUBSTRING_UTILS_CPP_
