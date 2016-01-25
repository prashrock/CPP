//g++ --std=c++11 -g -o algo_sort_num_smaller_elements_in_right algo_sort_num_smaller_elements_in_right.cc

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <set>               /* std::multiset                */
using namespace std;

/**
 * @file  Count number of smaller elements to right
 */

/**
 * You are given an integer array nums and you have to return a new counts
 * array. The counts array has the property where counts[i] is the number
 * of smaller elements to the right of nums[i].
 * Example:
 * Given nums = [5, 2, 6, 1]
 * To the right of 5 there are 2 smaller elements (2 and 1).
 * To the right of 2 there is only 1 smaller element (1).
 * To the right of 6 there is 1 smaller element (1).
 * To the right of 1 there is 0 smaller element.
 * Return the array [2, 1, 1, 0].
 */

/* --------------------Approach:1--------------------------- */
/** STL BST based approach using STL Multiset (duplicates)   *
 * Time Complexity = O(n^2).   Space Complexity = O(n)       *
 * Note: Multiset's iterators aren't random access iterators *
 * causing std::distance to be O(n) complexity               */
vector<int> countSmaller1(vector<int>& nums) {
    multiset<int> ms;
	vector<int> ans(nums.size(), 0);
	/*insert each number, calculate distance & store it in ans */
	for(int i = nums.size()-1; i >= 0; i--) {
		auto it = std::lower_bound(ms.begin(), ms.end(), nums[i]);
		ans[i] = std::distance(ms.begin(), it);
		ms.insert(nums[i]);
	}
	return ans;
}

/* --------------------Approach:2--------------------------- */
/** Insertion sort based approach with STL vectors           *
 * Time Complexity = O(n^2). Space Complexity = O(n)         *
 * Note: worst case complexity of insertion sort is O(n^2)   *
 * but average case is O(n lg n), so this is acceptable      *
 * Note: Distance in random access iterator is O(1)          */
vector<int> countSmaller2(vector<int>& nums) {
	vector<int> ans(nums.size(), 0), sorted;
	for(int i = nums.size()-1; i >= 0; i--) {
		auto it = std::lower_bound(sorted.begin(), sorted.end(), nums[i]);
		ans[i] = std::distance(sorted.begin(), it);
		sorted.insert(it, nums[i]);
	}
	return ans;
}


/* Approach 3 - BST + Rank after each insert                 */
/* Approach 4 - Merge sort + Count-inversions at each index  */

void dump(const vector<int> &a)
{
	for(auto val: a) cout << val << ", "; cout << endl;
}

bool match(const vector<int> &a, const vector<int> &b)
{
	return std::equal(a.begin(), a.end(), b.begin());
}

void error_dump(const vector<int> &a, const vector<int> &ans,
				const vector<int> &expected) {
	cout << "Error: Failed at Input: "; dump(a);
	cout << "       Expected: "; dump(expected);
	cout << "       Got: ";      dump(ans);
}


/* Given an input vector and expected result, valdiate it    */
int test_driver(vector<int> &a, const vector<int> &exp) {
	auto ans = countSmaller1(a);
	if(match(exp, ans) == false) { error_dump(a, ans, exp); return -1; }	
	else return 0;
}

int manual_test()
{
	int ret;
	vector<int> a = {2, 0, 1};
	vector<int> exp = {2, 0, 0};
	if(test_driver(a, exp) != 0) return -1;

	a = {5, 2, 6, 1};
	exp = {2, 1, 1, 0};
	if(test_driver(a, exp) != 0) return -1;

	a = {-1, -1};
	exp = {0, 0};
	if(test_driver(a, exp) != 0) return -1;
	
	return 0;
}

int main()
{
	if(manual_test() == 0)
		cout << "All manual test-cases passed." << endl;
}
