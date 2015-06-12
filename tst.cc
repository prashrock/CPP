//g++ -std=c++11 -o tst tst.cc
#include <iostream>          /* std::cout        */
#include <iomanip>           /* std::setw        */
#include <cmath>             /* pow              */
#include <algorithm>         /* std::swap        */

#include "./utils/print_utils.h"     /* print_table_row  */
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
