#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;
#include "rand_utils.h"

const int sides = 6;
inline int r_sides(){ return (rand() % sides + 1); }

int main()
{
	const int n_dice = 2, num_outcomes = n_dice * sides + 1;
	int trials;
	init_rand(); /* Seed random number generator    */
	int* outcomes = new int[num_outcomes];
	cout << "\nEnter Number of trials:" << endl;
	cin >> trials;
	for(int j = 0; j < trials; j++) {
		int d1 = r_sides();  /* First die outcome */
		int d2 = r_sides();  /* Second die outcome */
		outcomes[d1 + d2]++; /* Increment that outcome */
	}
	cout << "probability of sum of two die outcome:\n";
	for (int j = 2; j < num_outcomes; j++)
		cout << "value = " << j
			 << " probability = "
			 << static_cast<double> (outcomes[j])/trials
			 << endl;
	return 0;
}
