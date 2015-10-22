//g++ --std=c++11 -g -o distrib_duplicate_number distrib_duplicate_number.cc

/**
 * @file  Duplicate Number
 * @brief Find the integer that occurs twice.
 */

/**

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


/* This is a distributed election count algo which will      *
 * find the majority element (element occuring > half times) *
 * Since this problem doesnt make this claim, cant use this  */
int booyerMooreMethod(vector<int>& nums) {
	int candidate, cnt = 0;
	for(int i = 0; i < nums.size(); ++i) {
		if(cnt == 0)              candidate = nums[i];
		if(candidate == nums[i])  cnt++;
		else                      cnt--;
	}
	int verify_cnt = 0;
	for(int i = 0; i < nums.size(); ++i)
		if(candidate == nums[i]) verify_cnt++;
		
	if(verify_cnt >= (nums.size()+1)/2) return candidate;
	else                                return -1;
}

/* Use Linked List cycle detection algorithm.                *
 * - Credit: Tortoise & Hair algo (Don. Knuth, Floyd)        */
int findDuplicate(vector<int>& nums) {
	int hair = 0, tortoise = 0;
	do{
		tortoise = nums[tortoise];
		hair = nums[nums[hair]];
	} while(hair != tortoise);
	/* Find the beginning of the loop                        */
	tortoise =  0;
	while(hair != tortoise){
		tortoise = nums[tortoise];
		hair = nums[hair];
	}
	return tortoise;
}

int main()
{
	int ret;
	vector<int> a = {1, 1, 2};
	ret = findDuplicate(a);
	if(ret != 1) goto Errmain;

	a.clear();
	a = {3, 1, 3, 4, 2};
	ret = findDuplicate(a);
	if(ret != 3) goto Errmain;

	a.clear();
	a = {2, 2, 2, 2, 2};
	ret = findDuplicate(a);
	if(ret != 2) goto Errmain;

	a.clear();
	a = {3, 2, 2, 2, 4};
	ret = findDuplicate(a);
	if(ret != 2) goto Errmain;

	a.clear();
	a = {7, 9, 7, 4, 2, 8, 7, 7, 1, 5};
	ret = findDuplicate(a);
	if(ret != 7) goto Errmain;

	a.clear();
	a = {1, 3, 4, 2, 1};
	ret = findDuplicate(a);
	if(ret != 1) goto Errmain;

	a.clear();
	a = {9, 4, 9, 5, 7, 2, 8, 9, 3, 9};
	ret = findDuplicate(a);
	if(ret != 9) goto Errmain;

	cout << "All test-cases passed." << endl;
	return 0;
Errmain:
	cout << "Error: Find Duplicate returned " << ret << " for:" << endl;
	for(auto val: a) cout << val << ", "; cout << endl;
	return -1;
}
