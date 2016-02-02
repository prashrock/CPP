#include <fstream>           /* std::ifstream                */
#include <iostream>          /* std::cout                    */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */

#include "print_utils.h"     /* print_table_row, MILLION     */
#include "rand_generator.h"  /* init_rand()                  */
#include "math_prime.h"      /* prime test + prime generator */
using namespace std;

/* Generate all random numbers upto a given N                */
const int number_of_trials = 1;
const size_t num_rands     = 1000;
const int max_rand_val     = 100*MILLION;
const string ans_file      = "../math/1000_primes.txt";

/* Parse the result file and copy all primes to a vector     */
void parse_result_file(string file_name, std::vector<size_t> &vect)
{
	std::ifstream infile(file_name); /* Input file stream    */
	size_t word;
	if(infile.is_open() == false) {
		cout << "Error: " << file_name << " not found" << endl;
		return;
	}
	while(infile >> word)            /* Get next prime num   */
		vect.push_back(word);        /* Add prime to a vect  */
	cout << "Info: Input file '" << file_name
		 << "' parsed. Found " << vect.size() << " primes" << endl;
}

/* Call prime generator and verify output                    */
void prime_generate_test(std::vector<size_t> &ans)
{
	size_t i;
	std::vector<size_t> outp_e(num_rands);
	prime_seive_eratosthenes<num_rands>(&outp_e[0], max_rand_val);
	for(i = 0; i < outp_e.size() && i < ans.size(); ++i)
		if(outp_e[i] != ans[i]) break;
	if(i < ans.size())
	{
		cout << "Error: Seive numbers do not match answer. Expected "
			 << ans[i] << " found " << outp_e[i] << " i = " << i
			 << endl;
	}
	else
		cout << "Info: Seive results verified successfully" << endl;		
	//for(auto i : eratosthenes)
		//cout << i << ", ";
}

int main()
{
	std::vector<size_t> expected_primes;  /* Known primes    */
	init_rand();
	parse_result_file(ans_file, expected_primes);

	/* Generate prime and test with known good primes        */
	for(auto i = 0; i < number_of_trials; ++i) 
		prime_generate_test(expected_primes);
}
