#include <iostream>            /* std::cout   */
#include <cstdlib>
#include <vector>              /* std vector  */
#include "rand_generator.h"    /* init_rand() */
using namespace std;

const int sides = 6;
static inline int r_sides()
{
    return (get_rand(0, sides));
}

int main()
{
	const int n_dice = 2, num_outcomes = n_dice * sides + 1;
	int trials;
	init_rand(); /* Seed random number generator    */
	std::vector<int> outcomes(num_outcomes);
	std::vector<int> face_val(num_outcomes);

	for(int i = 0; i < num_outcomes; ++i)
		face_val[i] = i;
	
	cout << "\nEnter Number of trials:" << endl;
	cin >> trials;
	for(int j = 0; j < trials; j++) {
		int d1 = r_sides();  /* First die outcome */
		int d2 = r_sides();  /* Second die outcome */
		if(d1 + d2 >= num_outcomes)
			cout << "daiii" << d1 << " " << d2 << endl;
		outcomes[d1 + d2]++; /* Increment that outcome */
	}

	for (int j = 2; j < num_outcomes; j++)
		cout << "value = " << j
			 << " probability = "
			 << static_cast<double> (outcomes[j])/trials
			 << endl;

	return 0;
}
