//taskset 0x1 ./sort_test
#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <vector>            /* std:vector                   */
#include <chrono>            /* high_resolution_clock        */

#include "time_api.h"        /* C based time mgmt API        */
#include "math_shuffle.h"    /* math::shuffle implementation */
#include "rand_generator.h"  /* init_rand,fill_vector_rand   */
#include "print_utils.h"     /* print_table_row, MILLION     */
#include "insertion_sort.h"  /* insertion_sort               */
#include "merge_sort.h"      /* merge_sort                   */
using namespace std;

const size_t num_loops = 10000;      /* #Loops for each test */
const size_t num_elems = MILLION/10; /* max container size   */
const size_t num_tests = 3;

/* Keep STL sort as the first to compare results with others */
void (*func_arr[])(std::vector<int>::iterator, std::vector<int>::iterator) = {
   &std::sort, &sort::insertion_sort, &sort::merge_sort,
};

const std::vector<std::string> func_names = {
   "STL_sort", "Insertion", "MergeSort(R)"
};

/* Given two matrices where each row corresponds to a sort   *
 * result compare row by row the values across my_sort and   *
 * Expected sort output (STL sort)                           */
bool validate_sorted_vectors(std::vector<std::vector<int>>& my_sort,
                             std::vector<std::vector<int>>& exp,
                             std::string my_sort_func_name) {
   if(my_sort.size() != exp.size()) {
      cout << "Error: Sort Matrix size does not match " << my_sort.size()
           << " " << exp.size() << endl;
      return false;
   }
   for(size_t i = 0; i < my_sort.size(); ++i) {
      if(my_sort[i] != exp[i]) {
         cout << "Error:  and Exp differ in sorted output: " << endl;
         print_table_row(my_sort_func_name, my_sort[i]);
         print_table_row("STL Sort", exp[i]);
         return false;
      }
   }
   return true;
}

bool sort_perf_test_run(std::vector<std::vector<int>>& vv, size_t n_elems) {
   std::vector<std::chrono::milliseconds::rep>duration_ms(num_tests);
   std::vector<std::vector<int>> exp;
   /* For each sort algo(num_tests), calc time for n vectors */
   for(size_t i = 0; i < num_tests; ++i) {
      auto vv_cpy = vv;   /* Copy the input vector           */
      /* Measure time only to sort n different vectors       */
      auto begin = std::chrono::high_resolution_clock::now();
      for(auto &v : vv_cpy)  func_arr[i](v.begin(), v.end());
      auto end   = std::chrono::high_resolution_clock::now();
      duration_ms[i] = std::chrono::duration_cast<std::chrono::milliseconds>
         (end - begin).count();
      /* Assume STL sort is always correct-use as exp answer */
      if(i == 0) exp = vv_cpy;
      else if(validate_sorted_vectors(vv_cpy, exp, func_names[i]) == false)
         return false;
   }
   print_table_row<std::chrono::milliseconds::rep>(std::to_string(n_elems),
                                                   duration_ms, 20, 10);
   return true;
}

/* For each test print the banner (test_types and duration)  */
void print_banner(const std::string& test_name) {
   std::cout << test_name << ":  " << std::endl;
   print_table_row<std::string>("#elements", func_names, 20, 10);
   print_table_row<std::string>("", vector<string>(num_tests, "(in ms)"),
                                20, 10);
}

/* Compare performance of STL sort with my sort impl         */
bool sort_perf_test(size_t n_vectors=num_loops, int rand_max=10) {
   std::vector<size_t> n_elems = {1, 10, 100, 1000, 2000};
   /* Run battery of tests with increasing sequence          */
   print_banner("Increasing sequences");
   for(size_t i = 0; i < n_elems.size(); ++i) {
      vector<vector<int>> vv(n_vectors, std::vector<int>(n_elems[i]));
      /* Fill vector with an increasing sequence 0,1,..,n    */
      for(auto &v: vv) std::iota(v.begin(), v.end(), 0);
      if(sort_perf_test_run(vv, n_elems[i]) == false) return false;
   }
   
   /* Run next batch of tests with random unique sequence    */
   print_banner("Random Unique sequences");
   for(size_t i = 0; i < n_elems.size(); ++i) {
      std::vector<std::vector<int>> vv(n_vectors, std::vector<int>(n_elems[i]));
      /* Fill vector with an increasing sequence 0,1,..,n    */
      for(auto &v: vv) {
         std::iota(v.begin(), v.end(), 0);
         math::shuffle(v);
      }
      if(sort_perf_test_run(vv, n_elems[i]) == false) return false;
   }
   
   /* Run next batch of tests with random duplicate sequence */
   print_banner("Random Duplicate sequences");
   for(size_t i = 0; i < n_elems.size(); ++i) {
      std::vector<std::vector<int>> vv(n_vectors, std::vector<int>(n_elems[i]));
      for(auto &v: vv) fill_vector_rand(v, 0, rand_max);
      if(sort_perf_test_run(vv, n_elems[i]) == false) return false;
   }
   
   return true;
}


int main() {
   //   std::vector<int> a = {6, 3, 5, 4, 2, 1};
   //sort::merge_sort(a.begin(), a.end());
   //return 0;
   init_rand();
   if(sort_perf_test() == false) return -1;
   return 0;
}


