//g++ --std=c++11 -g -o ds_tree_verify_preorder_sequence_bst ds_tree_verify_preorder_sequence_bst.cc

/**
 * @file  BST verify pre-order sequence
 * @brief Given a vector verify if it is BST pre-order sequence
 */

#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string,                 */
#include <cstring>           /* std::strtok                  */
#include <queue>             /* std::priority_queue          */
using namespace std;

/*
 * Given an array of numbers, verify whether it is the correct preorder traversal
 * sequence of a binary search tree.
 * You may assume each number in the sequence is unique.
 * Follow up: Could you do it using only constant space complexity?
 */

//There is a stack based iterative solution posted on Leetcode
//https://leetcode.com/discuss/52060/72ms-c-solution-using-one-stack-o-n-time-and-space

/* Recursively do isBST after identifying left/right subtree */
bool verifyPreorder(vector<int>& vec, int start, int end, int min, int max) {
	/* Check if we are within the boundaries first           */
	if(start > end)               return true;

	int root = vec[start]; /* root @ current sub-tree        */
	/* Validate root @ current subtree, similar to isBST     */
	if(root < min || root > max)  return false;
	if(start == end)              return true;

	/* Use Bin-Search based UpperBound to get demarcation    */
	int i = start + 1; /* i to demarcate Left/Right Subtree  */
	/* Note: Upper bound needs the region to be [start, end) *
	 * now, i point to first elem in right subtree or end+1  */
	i = std::upper_bound(vec.begin()+i, vec.begin()+end+1, root) - vec.begin();

	/* Recursively visit Left & Right Sub-Trees to validate  */
	bool lhs = true, rhs = true;
	if(i > start + 1) /* If Left Sub-tree exists recurse     */
		lhs = verifyPreorder(vec, start+1, i-1, min, std::min(root, max));
	if(lhs)  /* If left Sub-tree passed then goto right      */
		rhs = verifyPreorder(vec, i, end, std::max(root, min), max);
	return lhs & rhs;
}

/**
 * @brief Recursive solution to verify Pre-order BST         *
 * @param vector of integers                                 *
 * @ret   bool representing if sequence is valid or not      *
 */
bool verifyPreorder(vector<int>& pre) {
	return verifyPreorder(pre, 0, pre.size()-1,
						  std::numeric_limits<int>::min(),
						  std::numeric_limits<int>::max());
}

int manual_test()
{
	vector<int> a = {};
	if(verifyPreorder(a) != true) {
		cout << "Error: Empty test-case failed" << endl;
		return -1;
	}
	a = {2, 1};
	if(verifyPreorder(a) != true) {
		cout << "Error: 2 node test-case failed" << endl;
		return -1;
	}
	a = {3, 1, 2};
	if(verifyPreorder(a) != true) {
		cout << "Error: 3 node test-case failed" << endl;
		return -1;
	}
	a = {2, 3, 1};
	if(verifyPreorder(a) != false) {
		cout << "Error: 3 node false test-case failed" << endl;
		return -1;
	}
	return 0;
}

int main()
{
	if(manual_test() == 0)
		cout << "Info: All manual test-cases passed" << endl;
	return 0;
}
