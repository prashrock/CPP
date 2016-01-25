//g++ --std=c++11 -Wall -g -o ds_string_strobogrammatic_num_i_ii_iii ds_string_strobogrammatic_num_i_ii_iii.cc

/**
 * @file  String Strobogrammatic Number
 * @brief Construct and Verify Strobogrammatic Numbers
 */


#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <unordered_map>     /* std::unordered_map container */
using namespace std;

/*
 * A strobogrammatic number is a number that looks the same when
 * rotated 180 degrees (looked at upside down).
 * Write a function to determine if a number is strobogrammatic.
 * The number is represented as a string.
 * For example, the numbers "69", "88", and "818" are all strobogrammatic.
 */

/* Maintain a mapping of numbers which form strobogrammatic  *
 * pairs. Note: this mapping can be used to create/verify    */
const std::vector<char> stchar = {'0', '1', '6', '8', '9'};
static std::unordered_map<char, char> stmap = {
      {'0', '0'},  /* Cannot occur in first/last pos         */
	  {'1', '1'},
	  {'6', '9'},  /* 6, 9 and 9,6 need to occur as a pair   */
	  {'8', '8'},
	  {'9', '6'}
}; 

/**
 * Similar to Palindrome check, but use strobe_map for checks*
 * @param num, string containing the proposed strob number   *
 * @return                                                   *
 *   True if number is Strobogrammatic; False if otherwise   *
 * Time Complexity = O(n),  n=len(num)                       *
 * Space Complexity= O(1)                                    */
bool isStrobogrammatic(string num) {
	auto fit = num.begin();
	auto rit = num.rbegin();
	for(; fit != num.end() && rit != num.rend(); ++fit, ++rit) {
		if     (stmap.find(*fit) == stmap.end()) return false;
		else if(stmap.find(*rit) == stmap.end()) return false;
		else if(stmap[*fit] != *rit)             return false;
		if(fit == rit.base())      break;  /* half-way there */
	}
	return true;
}

bool isStrobogrammatic_test() {
	if(isStrobogrammatic("2") == true)
		cout << "Error: '2' case failed (returned true)" << endl;
	else if(isStrobogrammatic("6") == true)
		cout << "Error: '6' case failed (returned true)" << endl;
	else if(isStrobogrammatic("69") == false)
		cout << "Error: '69' case failed (returned false)" << endl;
	else if(isStrobogrammatic("69") == false)
		cout << "Error: '69' case failed (returned false)" << endl;
	else if(isStrobogrammatic("88") == false)
		cout << "Error: '88' case failed (returned false)" << endl;
	else if(isStrobogrammatic("818") == false)
		cout << "Error: '818' case failed (returned false)" << endl;
	else {
		cout << "Info: All Strobogrammatic check cases passed." << endl;
		return true;
	}
	return false;
}

/**
 * Find all strobogrammatic numbers that are of length = n.
 * For example,
 * 	   Given n = 2, return ["11","69","88","96"].
 */

/**
 * Recursively try all possible combinations till n/2 pos    *
 * @param                                                    *
 *    fwd, rev - current fwd, reverse positions respectively *
 *    s        - current Strobogrammatic number being created*
 *    ans      - result vect with all Strobogrammatic numbers*/
void Strobo_recurse_generate(int fwd, int rev,
							 string &s, vector<string> &ans) {
	/* If fwd has crossed reverse, we are done constructing  *
	 * Push this result to the ans vector and return immdtly */
	if(fwd > rev)  {
		ans.push_back(s);
		return;
	}
	/* Else condition, try all combinations @fwd, @rev       */
	for(int i = 0; i < (int)stchar.size(); ++i) {
		/* 0 cannot be in first pos (except when len == 1).  *
		 * 6/9 cannot be in middle (i.e.,it has to be pairs) */
		if(fwd == 0  && (stchar[i] == '0') && s.size() != 1)      continue;
		else if(fwd == rev && (stchar[i]=='6' || stchar[i]=='9')) continue;
		s[fwd] = stchar[i];
		s[rev] = stmap[stchar[i]];
		Strobo_recurse_generate(fwd+1, rev-1, s, ans);
	}
}

/* Wrapper function to invoke recursive Strobo generator     */
vector<string> findStrobogrammatic(int n) {
	vector<string> ans;
	string s(n, '0');
	if(n != 0)    Strobo_recurse_generate(0, n-1, s, ans);
	return ans;
}

bool findStrobogrammatic_test() {
	int num;
	vector<string> res, exp;

	num = 1;
	res = findStrobogrammatic(num);
	exp = {"0", "1", "8"};
	if(res != exp) goto Err_FindStrobo;
	num = 2;
	res = findStrobogrammatic(num);
	exp = {"11", "69", "88", "96"};
	if(res != exp) goto Err_FindStrobo;
	num = 3;
	res = findStrobogrammatic(num);
	exp = {"101", "111", "181", "609", "619", "689", "808",
		   "818", "888", "906", "916", "986"};
	if(res != exp) goto Err_FindStrobo;
	
	cout << "Info: All Strobogrammatic generated successfully." << endl;
	return true;
Err_FindStrobo:
	cout << "Error: Strobogrammatic number generation failed for n="
		 << num << ", res=";
	for(auto elem : res) cout << elem << ", ";
	cout << endl;
	return false;
}

/**
 * Write a function to count the total strobogrammatic numbers that
 * exist in the range of low <= num <= high.
 * For example:
 * Given low = "50", high = "100", return 3. Because 69, 88, and 96 are
 * three strobogrammatic numbers.
 * Note: Because the range might be a large number, the low and high
 * numbers are represented as string.
 */

/**
 * Recursively try all possible combinations till n/2 pos    *
 * Additional checks involved to check if its within range   *
 * @param                                                    *
 *    fwd, rev - current fwd, reverse positions respectively *
 *    s        - current Strobogrammatic number being created*
 *    cnt      - #Strobogrammatic numbers found within range *
 *    low,high - Low and High Range for Strobogrammatic nums */
void Strobo_recurse_count(int fwd, int rev, string &s, int &cnt,
						  const string &low, const string &high) {
	/* If any iteration goes outofbounds, cancel recursion   */
	/* If end is reached, validate if this is within range   */
	if(fwd > rev)  {
		unsigned long val = stoul(s);
		if(val >= stoul(low) && val <= stoul(high)) cnt++;
		return;
	}
	/* Else condition, try all combinations @fwd, @rev       */	
	for(int i = 0; i < (int)stchar.size(); ++i) {
		/* 0 cannot be in first pos (except when len == 1).  *
		 * 6/9 cannot be in middle (i.e.,it has to be pairs) *
		 * If for any iteration, we go out of bounds, return */
		if(fwd == 0   && (stchar[i]=='0') && s.size() != 1)       continue;
		else if(fwd == rev && (stchar[i]=='6' || stchar[i]=='9')) continue;
		s[fwd] = stchar[i];
		s[rev] = stmap[stchar[i]];
		Strobo_recurse_count(fwd+1, rev-1, s, cnt, low, high);
	}
}
/* Wrapper function to invoke recursive Strobo generator     */
int strobogrammaticInRange(string low, string high) {
	int cnt = 0;
	for(int n = low.size(); n <= (int)high.size(); ++n) {
		string s(n, '0');
		Strobo_recurse_count(0, n-1, s, cnt, low, high);
	}
	return cnt;
}

bool strobogrammaticInRange_test() {
	string low, high;
	int cnt, exp;

	low = "1"; high = "1";
	cnt = strobogrammaticInRange(low, high);
	exp = 1;
	if(cnt != exp) goto Err_FindStroboRange;
	
	low = "50"; high = "100";
	cnt = strobogrammaticInRange(low, high);
	exp = 3;
	if(cnt != exp) goto Err_FindStroboRange;
	
	cout << "Info: All Strobogrammatic Range cnt successful." << endl;
	return true;
Err_FindStroboRange:
	cout << "Error: Strobogrammatic number Range cnt failed for low="
		 << low << ", high=" << high << ", cnt=" << cnt << endl;
	return false;
}

int main()
{
	if     (isStrobogrammatic_test() == false)      return -1;
	else if(findStrobogrammatic_test() == false)    return -1;
	else if(strobogrammaticInRange_test() == false) return -1;
	return 0;
}
