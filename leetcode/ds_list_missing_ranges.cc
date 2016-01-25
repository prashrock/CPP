//g++ --std=c++11 -g -o ds_list_missing_ranges ds_list_missing_ranges.cc

/**
 * @file  Missing Ranges
 * @brief Print all missing ranges between low, high
 */

/**
 * Given a sorted integer array where the range of elements are
 * [lower, upper] inclusive, return its missing ranges.
 * For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99,
 * return ["2", "4->49", "51->74", "76->99"].
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

/**
 * Iterate over all numbers, foreach number create lo, high  *
 * points. If lo=high, push 1 number, else, push range       *
 * @param:                                                   *
 *  nums  - input numbers whose inbetween ranges we need     *
 *  lower - lower number which should be <= nums[0]          *
 *  upper - higher number which should be >= nums[n]         *
 * @returns: a vector of strings of missing ranges           *
 * Time Complexity = O(n),  Space Complexity= O(1)           */
vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
	vector<string> ans;
	for(int i = 0, lo, hi; i <= nums.size(); ++i) {
		if     (nums.size() == 0)  { lo = lower;       hi = upper;     }
		else if(i == 0)            { lo = lower;       hi = nums[i]-1; }
		else if(i == nums.size())  { lo = nums[i-1]+1; hi = upper;     }
		else                       { lo = nums[i-1]+1; hi = nums[i]-1; }

		if     (hi == lo)       ans.push_back(std::to_string(lo));
		else if(hi >  lo)       ans.push_back(std::to_string(lo) + "->" +
											  std::to_string(hi));
	}
	return ans;
}



int main()
{
	vector<int> input;
	vector<string> ans, exp;

	input = {};
	ans = findMissingRanges(input, 1, 1);
	exp = {"1"};
	if(ans != exp) goto Errmain;

	input = {0, 1, 3, 50, 75};
	ans = findMissingRanges(input, 0, 99);
	exp = {"2", "4->49", "51->74", "76->99"};
	if(ans != exp) goto Errmain;

	cout << "All test-cases passed." << endl;
	return 0;
Errmain:
	cout << "Error: Failed for below test-case" << endl;
	for(auto elem : input) cout << elem << " ,";
	cout << endl << "Got:" << endl;
	for(auto elem : ans) cout << elem << " ,";
	cout << endl << "Expected:" << endl;
	for(auto elem : exp) cout << elem << " ,";
	cout << endl;
	return -1;
}
