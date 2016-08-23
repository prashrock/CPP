#include <iostream>              /* std::cout                */
#include <vector>                /* std::vector              */
#include <cmath>                 /* pow, log2                */
#include <cassert>               /* assert                   */
#include <algorithm>             /* std::max                 */
#include <random>              /* std::default_random_engine */

#include "rand_generator.h"      /* init_rand()              */
#include "binary_tree.h"         /* BT API                   */
#include "binary_indexed_tree.h" /* Binary Indexed Tree API  */
#include "print_utils.h"         /* print_table_row          */
using namespace std;
using namespace bt;

const int num_iters   =  1;
const int num_inserts =  15;
const int min_key     =   0;
const int max_key     =  30;

/* Walk through BT creation and deletion process  */
void bt_walkthrough()
{
   std::vector<int> vec(num_inserts);
   binary_tree<int, int> bt;
   
   fill_vector_rand(vec, min_key, max_key);
   print_table_row<int>("Insert order", vec);
	
   cout << "Walkthrough of BT operations:" << endl;
   cout << "Inserting " << vec.size() << " elements" << endl;
   for(auto key : vec) {
      bt.ins(key, key);
      cout <<   "elem = " << key
           << " size  = " << bt.size()
           << " levels= " << bt.height() << endl;
   }

   print_table_row<int>("Preorder",  bt.get_keys(Traversal::PREORDER));
   print_table_row<int>("Inorder",   bt.get_keys(Traversal::INORDER));
   print_table_row<int>("Postorder", bt.get_keys(Traversal::POSTORDER));
   print_table_row<int>("BFS",       bt.get_keys(Traversal::BFS));
   print_table_row<int>("Spiral",    bt.get_keys(Traversal::SPIRALORDER));
   print_table_row<int>("Bottom-up", bt.get_keys(Traversal::BOTTOMUPORDER));
	
   cout << "Pretty Printer:" << endl;
   cout << bt;
	
   std::shuffle(vec.begin(), vec.end(),
                std::default_random_engine(get_rand(max_key)));

   int lcp;
   if(bt.find_lcp(vec[0], vec[1], lcp))
      cout << "LCP of " << vec[0] << "," << vec[1] << " is " << lcp << endl;
   else
      cout << "No LCP for " << vec[0] << "," << vec[1] << " failed" << endl;

   /* Verify Serialize/DeSerialize APIs                     */
   string serial;
   bt::serialize(bt.get_root(), serial);
   cout << "serialized string:" << serial << endl;
   binary_tree<int, int> serial_bt(serial);
   cout << "Below is Deserialized BT:"    << endl;
   cout << serial_bt;
   cout << "Size = " << serial_bt.size()  << endl;
	
   print_table_row<int>("Del order", vec);

   for(auto key : vec) {
      bt.del(key);
      cout << "size   = " << bt.size()
           << " levels= " << bt.height()
           << endl;
   }
   cout << "-----------------------" << endl;
   cout << "Info: BT Walkthrough complete" << endl;
}

/* Manually crafted test-cases to validate BT functionality  */
bool bt_manual_test()
{
   bool ret = false;
   std::vector<int> vec(num_inserts);
   binary_tree<int, int> bt;

   /*  Generate vector contents randomly */
   //kp_cnt = 0;
   fill_vector_rand(vec, min_key, max_key);
   auto del_vec = vec;	
   auto exp_ht = static_cast<unsigned> (ceil(log2(vec.size() + 1)));
											
   /* Insert operation and associated test-cases            */
   for(auto key : vec) bt.ins(key, key);
											
   if(bt.size() != vec.size())
      cout << "Error: After insert, BT size incorrect. Expecting "
           << vec.size() << " got " << bt.size() << endl;
   else if(bt.height() != exp_ht)
      cout << "Error: After insert, BT height incorrect. Expecting "
           << exp_ht << " got " << bt.height() << endl;
   else ret = true;
   if(ret == false) goto manual_test_end;
	
   /* Delete operation and associated test-cases            */
   //std::shuffle(vec.begin(), vec.end(),
   //             std::default_random_engine(get_rand(max_key)));
   sort(del_vec.begin(), del_vec.end());
   del_vec.erase(unique(del_vec.begin(), del_vec.end()), del_vec.end());
   for(auto key : del_vec) {
      if(bt.find(key) == false) {
         cout << "Error: key " << key << " missing." << endl;
         ret = false;
         goto manual_test_end;
      }
      bt.del(key);
   }	
   if(bt.size() != 0)
      cout << "Error: After delete, BT size incorrect. Expecting "
           << 0 << " got " << bt.size() << endl;
   //if(kp_cnt != vec.size())
   //	cout << "Error: After delete, Destructor cnt err. Expecting "
   //        << vec.size() << " got " << kp_cnt << endl;
	
 manual_test_end:
   if(ret == false) {
      print_table_row<int>("Input_vec", vec);
      print_table_row<int>("Del_vec", del_vec);
   }
   return ret;
}

/* Given a vector and its equivalent contents in BIT format  *
 * use std::accumulate and bit ops to check both contents    */
bool validate_bi_tree_and_vector(std::vector<int>& vec,
                                 bin_idx_tree<int>& bi_tree) {
   /* 1) Verify if BIT and Vector have the same size         */
   if(bi_tree.size() != vec.size()) return false;
   /* 2) Check the value at each index across BIT and Vector */
   for(size_t i = 0; i < vec.size(); ++i) {
      if(vec[i] != bi_tree.getVal(i)) {
         cout << "Error: BIT validate failed at " << i
              << " expected val=" << vec[i]
              << " got=" << bi_tree.getVal(i)     << endl;
         return false;
      }
   }
   /* 3) Check range sum [0, idx] for each index             */
   for(auto it = vec.begin(); it != vec.end(); ++it) {
      size_t idx= std::distance(vec.begin(), it);
      auto sum  = std::accumulate(vec.begin(), it+1, 0);
      auto bsum = bi_tree.getSum(idx);
      if(sum != bsum) {
         print_table_row<int>("Input_vec", vec);
         cout << "Error: BIT Sum failed at " << idx
              << " expected sum=" << sum << " got=" << bsum << endl;
         return false;
      }
   }
   return true;
}

bool bit_random_test(size_t N = num_inserts,
                     size_t n_updates = 10000) {
   std::vector<int> vec(N);
   fill_vector_rand(vec, min_key, max_key);
   bin_idx_tree<int> bi_tree(vec);
   /* Validate the sum before doing any operations on BIT    */
   if(validate_bi_tree_and_vector(vec, bi_tree) == false) return false;
   /* Perform random updates on BIT and then check result    */
   for(size_t i = 0; i < n_updates; ++i) {
      size_t idx = get_rand(0, N-1);
      int val = get_rand(max_key);
      vec[idx] += val;
      bi_tree.update(idx, val);
   }
   if(validate_bi_tree_and_vector(vec, bi_tree) == false) return false;
   /* Perform random range_sum checks on BIT                 */
   for(size_t i = 0; i < n_updates; ++i) {
      size_t b = get_rand(0, N-2), e = get_rand(b, N-1);
      int exp_sum = 0;
      for(size_t j = b; j <= e; ++j) exp_sum += vec[j];
      if(exp_sum != bi_tree.getSum(b, e)) {
         cout << "Error: BIT RangeSum failed @ [" << b << "," << e
              << "] expected sum=" << exp_sum
              << " got=" << bi_tree.getSum(b, e) << endl;
         return false;
      }
   }
   /* Validate the sum after doing range_sum checks on BIT   */
   if(validate_bi_tree_and_vector(vec, bi_tree) == false) return false;
   cout << bi_tree;
   cout << "Info: Binary Indexed Tree randomized test-cases complete" << endl;
   return true;
}

int main()
{
   init_rand();
   bt_walkthrough();
   for(int i = 0; i < num_iters; ++i)
      if(bt_manual_test() == false)    return -1;
   
   if(bit_random_test() == false)      return -1;
   cout << "Info: All manual tests passed successfully" << endl;
   return 0;
}
