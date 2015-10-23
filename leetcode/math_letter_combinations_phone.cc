//g++ --std=c++11 -g -o math_letter_combinations_phone math_letter_combinations_phone.cc

/**
 * @file  Letter Combinations of a Phone Number
 * @brief Given a list of numbers find all combinations of words
 */

/**
 * Given a digit string, return all possible letter combinations that
 * the number could represent.
 * Input:Digit string "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 * Note:
 *  - Although the above answer is in lexicographical order, your
 *    answer could be in any order you want.
 */


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow, tgamma(factorial)       */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
using namespace std;

/* Input set */
vector<vector<char> > set = {
	{'a','b','c'},       /* 2 */
	{'d','e','f'},       /* 3 */
	{'g','h','i'},       /* 4 */
	{'j','k','l'},       /* 5 */
	{'m','n','o'},       /* 6 */
	{'p','q','r','s'},   /* 7 */
	{'t','u','v'},       /* 8 */
	{'w','x','y','z'},   /* 9 */
};
vector<string> ans;     /* Final vector of all possible strs */
vector<char>  cur_ans;  /* Current recursive combination     */

/* Generate all possible combinations of strings starting at *
 * current IDX till end of string                            *
 * @param digits - input string of digits                    *
 * @param pos    - current position in digits string         */
void Combine(string digits, int pos) {
	/* Base case                                             */
	/* 1) We've reached end of one combination. Write to ans */
	if(pos == digits.size())
		ans.push_back(std::string(cur_ans.begin(), cur_ans.end()));

    /* Special case                                          */
	/* 2) Digits has 0/1, no combination possible, continue  */
	else if(digits[pos] == '0' || digits[pos] == '1') {
		cur_ans[pos] = ' ';
		Combine(digits, pos + 1);
	}
	
	/* 3) Recursive combinatorial step                       */
	else {
		int table_idx = digits[pos] - '2';
		for(int i = 0; i < set[table_idx].size(); ++i) {
			cur_ans[pos] = set[table_idx][i];
			Combine(digits, pos+1);
		}
	}
}

/* Driver for above combination logic                          */
vector<string> letterCombinations(string digits) {
	/* #Combinations = (#ways_to_chose_1_digit_char)^(#digits) */
	int nCr = 1;
	for(int i = 0; i < digits.size(); ++i)
		if(digits[i] >= '2' && digits[i] <= '9')
			nCr *= set[(digits[i] - '2')].size();
	cout << "#Combinations possible = " << nCr << endl;

	cur_ans.resize(digits.size()); /* Each ans == digits.size()*/
	if(digits.size())              /* Spl case, digits empty   */
		Combine(digits, 0);
	return ans;
}

int main()
{
	letterCombinations("1023");
	for(auto itr = ans.begin(); itr != ans.end(); ++itr)
		cout << *itr << ", ";
	cout << endl;
	cout << "Ans length = " << ans.size() << endl;
	return 0;
}
