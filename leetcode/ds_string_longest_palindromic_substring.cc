//g++-5 --std=c++11 -g -o ds_string_longest_palindromic_substring ds_string_longest_palindromic_substring.cc

/**
 * @file  Longest Palindromic Substring
 * @brief Given a string return longest palindromic substring
 */

// https://leetcode.com/problems/longest-palindromic-substring/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
using namespace std;

/**
 * Given a string S, find the longest palindromic substring in S.
 * You may assume that the maximum length of S is 1000, and there
 * exists one unique longest palindromic substring.
 */

inline void expand(string& s, int b, int e, int& pb, int& plen) {
   /* Loop termination takes b, e just beyond the boundary   */
   for(; b >= 0 && e < s.size() && s[b] == s[e]; --b, ++e);
   size_t new_len = e - b + 1;
   /* Since b and e are beyond boundary, we have 2 extra     *
    * chars being considered.                                */
   if(new_len - 2 > plen) {
      plen = new_len - 2;
      pb   = b + 1;
   }
}

/** Expand around the center approach                        *
 * Time complexity : O(n^2)  Space complexity : O(1)         *
 * Inspired by Approach 4 of Leetcode solution               *
 * We observe that a palindrome mirrors around its center.   *
 * Therefore, a palindrome can be expanded from its center,  *
 * and there are only (2n - 1) such centers.                 *
 * You might be asking why there are (2n-1) & not n centers? *
 * The reason is the center of a palindrome can be in between*
 * two letters. Such palindromes have even number of letters *
 * (such as 'abba') and its center are between the two 'b' s */
std::string longestPalindrome(std::string s) {
   int plen = 1, pb = 0;
   /* 0/1 char string, return string itself                  */
   if(s.size() < 2) return s;
   /* Go from beginning till last but 1 character            */
   for(size_t i = 0; i < s.size() - 1; ++i) {
      expand(s, i, i, pb,  plen); /* expand assuming odd len */
      expand(s, i, i+1,pb, plen); /* expand assuming even len*/
   }
   return s.substr(pb, plen);
}

/* Note: this can also be solved by improvising on longest   *
 * common substring (with reverse as 2nd string) or by using *
 * Manacher's algorithm (check String notes)                 */

struct test_vector {
   std::string s;
   std::string exp;
};

const struct test_vector test[10] =  {
   { "a",         "a"         },
   { "aba",       "aba"       },
   {"aaabaaa",    "aaabaaa"   },
   {"aaabbaaaa",  "aaabbaaa"  },
   {"aaaabbaaa",  "aaabbaaa"  },
   {"aaba",       "aba"       },
   {"abaa",       "aba"       },
   { "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabcaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" },
    {"jglknendplocymmvwtoxvebkekzfdhykknufqdkntnqvgfbahsljkobhbxkvyictzkqjqydczuxjkgecdyhixdttxfqmgksrkyvopwprsgoszftuhawflzjyuyrujrxluhzjvbflxgcovilthvuihzttzithnsqbdxtafxrfrblulsakrahulwthhbjcslceewxfxtavljpimaqqlcbrdgtgjryjytgxljxtravwdlnrrauxplempnbfeusgtqzjtzshwieutxdytlrrqvyemlyzolhbkzhyfyttevqnfvmpqjngcnazmaagwihxrhmcibyfkccyrqwnzlzqeuenhwlzhbxqxerfifzncimwqsfatudjihtumrtjtggzleovihifxufvwqeimbxvzlxwcsknksogsbwwdlwulnetdysvsfkonggeedtshxqkgbhoscjgpiel", "sknks"},
    {"gphyvqruxjmwhonjjrgumxjhfyupajxbjgthzdvrdqmdouuukeaxhjumkmmhdglqrrohydrmbvtuwstgkobyzjjtdtjroqpyusfsbjlusekghtfbdctvgmqzeybnwzlhdnhwzptgkzmujfldoiejmvxnorvbiubfflygrkedyirienybosqzrkbpcfidvkkafftgzwrcitqizelhfsruwmtrgaocjcyxdkovtdennrkmxwpdsxpxuarhgusizmwakrmhdwcgvfljhzcskclgrvvbrkesojyhofwqiwhiupujmkcvlywjtmbncurxxmpdskupyvvweuhbsnanzfioirecfxvmgcpwrpmbhmkdtckhvbxnsbcifhqwjjczfokovpqyjmbywtpaqcfjowxnmtirdsfeujyogbzjnjcmqyzciwjqxxgrxblvqbutqittroqadqlsdzihngpfpjovbkpeveidjpfjktavvwurqrgqdomiibfgqxwybcyovysydxyyymmiuwovnevzsjisdwgkcbsookbarezbhnwyqthcvzyodbcwjptvigcphawzxouixhbpezzirbhvomqhxkfdbokblqmrhhioyqubpyqhjrnwhjxsrodtblqxkhezubprqftrqcyrzwywqrgockioqdmzuqjkpmsyohtlcnesbgzqhkalwixfcgyeqdzhnnlzawrdgskurcxfbekbspupbduxqxjeczpmdvssikbivjhinaopbabrmvscthvoqqbkgekcgyrelxkwoawpbrcbszelnxlyikbulgmlwyffurimlfxurjsbzgddxbgqpcdsuutfiivjbyqzhprdqhahpgenjkbiukurvdwapuewrbehczrtswubthodv", "jtdtj"},
};

int main()
{
   for(auto tst : test) {
      auto ans = longestPalindrome(tst.s);
      if(ans != tst.exp) {
         cout << "Error:longestPalindrome failed for "
              << tst.s << " Exp '" << tst.exp
              << "' Got '" << ans  << "'" << endl;
         return -1;
      }
   }
   cout << "Info: All manual testcases passed" << endl;
   return 0;
}
