//g++ --std=c++11 -g -o algo_dp_longest_increasing_subsequence algo_dp_longest_increasing_subsequence.cc

/**
 * @file  Longest Increasing Subsequence
 * @brief Given unsorted int arr, find len of longest increasing subsequence
 */

/**
 * Given an unsorted array of integers, find the length of longest
 * increasing subsequence. For example,
 *    Given [10, 9, 2, 5, 3, 7, 101, 18],
 * The longest increasing subsequence is [2, 3, 7, 101], so length is 4.
 * Note that there may be more than one LIS combination, it is only
 * necessary for you to return the length.
 * 
 * Your algorithm should run in O(n2) complexity.
 * Follow up: Could you improve it to O(n log n) time complexity?
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
 * DP approach to construct length memoization table. At     *
 * each element, the max length is either the max length @   *
 * current node or the max length of any previous node + 1   *
 * @param nums                                               *
 *   Input unsorted integer vector                           *
 * @ret   Max length of the LIS                              *
 * Time Complexity = O(n^2), Space Complexity = O(n)         */
int DP_lengthOfLIS(vector<int>& nums) {
	/* First handle base-case where input is empty           */
	if(nums.size() == 0) return 0;

	/* We do not need a 2D DP Memoization table as we only   *
	 * need to compute the length of the LIS. Init table     *
	 * to 1, bcoz each element is an LIS by itself           */
	int max_len = 1;
	vector<int> dp(nums.size(), 1);

	/* O(n^2) loop to check each element against all prev    *
	 * elements while maintaining max length at each node    */
	for(int i = 0; i < nums.size(); ++i) {
		for(int j = 0; j < i; ++j) {
			if(nums[i] > nums[j])
				dp[i] = std::max(dp[i], dp[j] + 1);
		}
		max_len = std::max(max_len, dp[i]);
	}

	return max_len;
}

/**
 * Patience sort based approach. Only store the last element *
 * in each group.                                            *
 * std::lower_bound() which might internally be binary search*
 * based offers O(lg n) complexity when working with a random*
 * access iterator (vector iterator)                         *
 * @param nums                                               *
 *   Input unsorted integer vector                           *
 * @ret   Max length of the LIS                              *
 * Time Complexity = O(nlgn), Space Complexity = O(n)        *
 * Inspired by Patience sort in Geeks4Geeks + Wiki           *
 * http://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n */
int PatienceSortBased_lengthOfLIS(vector<int>& nums) {
	/* First handle base-case where input is empty           */
	if(nums.size() == 0) return 0;

	vector<int> v;
	v.reserve(nums.size()); /* Max size == nums.size         */
	v.push_back(nums[0]);

	for(int i = 1; i < nums.size(); ++i) {
        /* 1) New smallest value found. Replace cur smallest */
		if(nums[i] < v[0])
			v[0] = nums[i];
		/* 2) If not smallest, find out where to put it      */
		auto it = std::lower_bound(v.begin(), v.end(), nums[i]);
		/* 2-a) Largest element. Add to end of vector        */
		if(it == v.end())
			v.push_back(nums[i]);
		/* 2-b) Take over next largest element found         */
		else
			*it = nums[i];
	}
	/* The number of elements in this result vector gives us *
	 * the longest increasing subsequence length             */
	return v.size();
}

int main()
{
	vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
	cout << DP_lengthOfLIS(a) << endl;
	cout << PatienceSortBased_lengthOfLIS(a) << endl;
}
