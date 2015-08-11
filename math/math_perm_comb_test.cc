//g++ --std=c++11 math_perm_comb_test_standalone.cc 
#include "math_perm_comb.h"   /* nCk                          */
using namespace std;

void combination_test()
{
	unsigned n, k, result;
	cout << "Computes nCk:" << endl
		 << "Please enter n = ";
	cin  >> n;
	cout << "Please enter k = ";
	cin  >> k;
	if(nCk(n, k, result))
		cout << n << "C" << k << " = "
			 << result << endl;
	else
		cout << n << "C" << k << " invalid or overflowed!!"
			 << endl;
}

int main()
{
	combination_test();
}
