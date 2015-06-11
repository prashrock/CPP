#include <iostream>   /* std::cout */
#include <algorithm>  /* std::max  */
#include "dyn_prog_helper.h"

using namespace std;
const int copy_overhead = 3;
const int manual_mode = 6;

void num_keystrokes_calculator(int n)
{
	int *table = new int[n+1];
	table[0] = 0;
	for(int i = 1; i <= n; ++i)
	{
		int cpy_max = 0;
		if(i <= manual_mode) table[i] = i;
		for(int j = i-1-copy_overhead; j > manual_mode; j--)
		{
			cpy_max = std::max(cpy_max, (j * 2));
		}
		table[i] = std::max(i, cpy_max);
	}
	cout << "Table calculation: " << endl;
	for(auto i : table)
		cout << i << " ";
	cout << endl;
	delete table;
}

int main()
{
	int n;
	cout << "Please enter the number of key strokes: ";
	cin >> n;
	num_keystrokes_calculator(n);
}
