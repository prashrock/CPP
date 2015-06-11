#include <iostream>   /* std::cout        */
#include <iomanip>    /* std::setw        */
#include <vector>     /* std::vector      */
#include <cmath>      /* pow              */
#include <cassert>    /* assert           */
#include <algorithm>  /* std::max         */

#include "print_utils.h"       /* print_table_row */
#include "rand_generator.h"    /* init_rand() */
using namespace std;

/* Find the median element in a sorted array   *
 * Time Complexity=O(1), Space Complexity=O(1) */
template<typename T>
static inline T median(const T v[], size_t n)
{
	int mid = n/2;
	if(n % 2 == 1)
		return v[mid];
	else
		return (v[mid-1] + v[mid])/2;
}

/* Divide and Conquer approach to find the median *
 * of two sorted arrays of the same length.       *
 * At each stage, split both arrays into two and  *
 * look at only one-half of the array.            *
 * The trick is to include n/2+1 elements because *
 * median can straddle the n/2 boundary           *
 * Note: This idea can easily be extended to cover*
 * the case where both array lengths are different*
 * Time Complexity=O(lg n), Space Complexity=O(1) */
template<typename T>
static inline T median(const T v1[], const T v2[], size_t n)
{
	/* Divide and Conquer base cases */
	/* Error base-case */
	if(n <= 0) {
		cout << "Error: Array empty. " << n << endl;
		return 0;
	}
	/* This base case is only needed when array   *
	 * lengths are unequal.                       *
	 * Note: even+even = odd+odd = even length    */
	else if(n == 1)
		return (v1[0] + v2[0]) / 2;
	/* Actual base-case. Note, median calculation *
	 * must consider 2 elements in each array     */
 	else if(n == 2)
	   	return (std::max(v1[0], v2[0]) + std::min(v1[1], v2[1])) / 2;

	/* Recursive cases                            */
	/* Middle element of (n/2)+1 array depends on *
	 * value of n (even/odd)                      */
	int mid;
	int half_size = n/2 + 1;
	T m1 = median(v1, n); /* Use median calculator*/
	T m2 = median(v2, n); /* Use median calculator*/
	if(n % 2 == 0) mid=(n/2)-1; /* even case      */
	else           mid=(n/2);   /* odd  case      */
	/* If middle elements are equal, we are done  */
	if (m1 == m2)
		return m1;
	/* If first array's middle element is bigger  *
	 * we can ignore the 2nd half of first array  */
	else if(m1 > m2)
		return median(&v1[0], &v2[mid], half_size);
	else
		return median(&v1[mid], &v2[0], half_size);
}

/* Driver function to test the median logic above *
 * Use random numbers to test                     */
void median_tester(size_t len, int count)
{
	cout << "Doing " << count << " median tests with length : " << len
		 << " - ";
	for(int i = 0; i < count; i++)
	{
		std::vector<int> v1(len), v2(len), val_vec;
		
		/* Generate vector contents randomly */
		fill_vector_rand(v1, 0, 20);
		fill_vector_rand(v2, 0, 20);
		val_vec = v1;
		val_vec.insert(val_vec.end(), v2.begin(), v2.end());
		
		/* Sort both random input vectors */
		std::sort(v1.begin(), v1.end());
		std::sort(v2.begin(), v2.end());
		std::sort(val_vec.begin(), val_vec.end());

		
		int med = median<int>(&v1[0], &v2[0], v1.size());
		int correct_median = median<int>(&val_vec[0], val_vec.size());
		if(med != correct_median)
		{
			cout << endl;
			cout << "Error: median " << med << " wrong. Expecting "
				 << correct_median << " (Iteration:"
				 << i << ")" << endl;
			print_table_row<int>("v1", v1);
			print_table_row<int>("v2", v2);
			return;
		}
	}
	cout << "Success" << endl;
}

int main()
{
	init_rand();
	//int len;
	//cout << "Please enter the size of the both arrays: ";
	//cin >> len;
	//median_tester(len, 1000);
	for(int i = 1; i <= 20; i++)
		median_tester(i, 10000);
}

