//g++ --std=c++11 -g -o divconq_elem_appear_once_in_sorted_arr divconq_elem_appear_once_in_sorted_arr.cc

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
 * @file  Find the element that appears once in a sorted array
 */

/**
 * Given a sorted array in which all elements appear twice 
 * (one after one) and one element appears only once. Find
 * that element in O(log n) complexity.
 * Example:
 *   Input:   arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8}
 *   Output:  4
 *   Input:   arr[] = {1, 1, 3, 3, 4, 4, 5, 5, 7, 7, 8}
 *   Output:  8
 */

/**
 * @brief:                                                   *
 * Note, input must be sorted, all elements must occur twice *
 * except one and the length of input must be odd (1 elem    *
 * without pair)                                             *
 * Time Complexity = O(lg n).   Space Complexity = O(1)      */
int findDuplicate(const vector<int>& nums, int start, int end) {
	int len = end - start + 1;
	int mid = start + (len/2);

    /* Base-case                                             */
	if(len == 1)  return nums[start];
	
	/* Check middle element match condition                  */
	if(nums[mid] == nums[mid-1])              mid = mid - 1;
	else if(nums[mid] != nums[mid+1])         return nums[mid];
	
	int left_len  = (mid - 1) - start + 1;
	int right_len = end - (mid + 2)   + 1; 

	//cout << "left:"  << start       << " " << left_len  << endl;
	//cout << "right:" << (mid + 2)   << " " << right_len << endl;
	
	/* Now check which half has odd-len and recurse          */
	if(left_len % 2) return findDuplicate(nums, start,  mid - 1);
	else             return findDuplicate(nums, mid + 2, end);
}

void dump_vector(const vector<int> &a)
{
	for(auto val: a) cout << val << ", "; cout << endl;
}

void error_dump(const vector<int> &a, int ret) 
{
	cout << "Error: Find Duplicate returned " << ret << " for:" << endl;
	dump_vector(a);
}

/* Given an input vector and expected result, valdiate it    */
int test_driver(const vector<int> &a, int result) {
	int ret;
	if(a.size() % 2 == 0) return -1; /* vect len must be odd */
	ret = findDuplicate(a, 0, a.size()-1);
	if(ret != result) { error_dump(a, ret); return -1; }	
	else return 0;
}

/* Generate all permutations and test. i.e., for n = 3,      *
 * auto-test will generate the following permutations:       * 
 * 1, 2, 2, 3, 3                                             *
 * 1, 1, 2, 3, 3                                             *
 * 1, 1, 2, 2, 3                                             */
int auto_test(int n)
{
	int idx, ret;
	int cnt = 2*n - 1;
	vector<int> ab(cnt, 0);
	for(int i = 0; i < n; ++i) {
		for(int j = 0, idx = 0; j < n; ++j) {
			ab[idx++] = j+1;
			if(i != j) ab[idx++] = j+1;
		}
		//dump_vector(ab);
		if(test_driver(ab, i+1) != 0) return -1;
	}
	return 0;
}

int manual_test()
{
	int ret;
	vector<int> a = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8};
	if(test_driver(a, 4) != 0) return -1;
	a.clear();

	a = {1, 1, 3, 3, 4, 4, 5, 5, 7, 7, 8};
	ret = findDuplicate(a, 0, a.size()-1);
	if(test_driver(a, 8) != 0) return -1;

	return 0;
}

int main()
{
	if(manual_test() == 0)
		cout << "All manual test-cases passed." << endl;
	if(auto_test(8) == 0 && auto_test(9) == 0)
		cout << "All auto test-cases passed." << endl;
}
