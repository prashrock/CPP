//g++ -std=c++11 -o tst tst.cc
/* Given the array of integers containing equal number of even *
 * and odd numbers. Rearrange the array such that even number  *
 * is at even place and odd number is at odd place.            *
 * Example : [2,1,3,4,7,9,24,98]                               *
 * Answer  : 1,2,3,4,7,24,9,98                                 */
#include <iostream>          /* std::cout                      */
#include <iomanip>           /* std::setw                      */
#include <cmath>             /* pow                            */
#include <algorithm>         /* std::swap                      */
#include <vector>            /* std:vector                     */

#include "../utils/print_utils.h"     /* print_table_row       */
using namespace std;

void even_odd_sorter(std::vector<int> val)
{
	print_table_row<int>("input:", val);
	for(int even = 0, odd = 1; even < val.size() && odd < val.size();)
	{
		if(val[even] % 2 != 0)     even += 2;
		else if(val[odd] % 2 == 0) odd  += 2;
		else                       std::swap(val[even], val[odd]);
	}
	print_table_row<int>("output:", val);
}

int main()
{
	//std::vector<int> val{2, 5, 8, 6, 11, 23, 18, 1, 9, 10};
	std::vector<int> val{2, 1, 3, 4, 7, 9, 24, 98};
	even_odd_sorter(val);
}
