#include <iostream>            /* std::cout     */
#include <iomanip>             /* std::setw     */
#include <vector>              /* std::vector   */
#include <cmath>               /* pow, log2     */
#include <cassert>             /* assert        */
#include <algorithm>           /* std::max      */

#include "rand_generator.h"    /* init_rand()   */
#include "binary_tree.h"       /* BT API        */
#include "print_utils.h"       /*print_table_row*/
using namespace std;
using namespace bt;

const int num_iters   =  100;
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

	print_table_row<int>("Preorder", bt.get_keys(Traversal::PREORDER));
	print_table_row<int>("Inorder", bt.get_keys(Traversal::INORDER));
	print_table_row<int>("Postorder", bt.get_keys(Traversal::POSTORDER));
	print_table_row<int>("BFS", bt.get_keys(Traversal::BFS));
	print_table_row<int>("Spiral", bt.get_keys(Traversal::SPIRALORDER));
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
	
	print_table_row<int>("Del order", vec);

	for(auto key : vec) {
		bt.del(key);
		cout << "size   = " << bt.size()
			 << " levels= " << bt.height()
			 << endl;
	}
	cout << "-----------------------" << endl << endl;
}

/* Manually crafted test-cases to validate BT functionality  */
bool bt_manual_test()
{
	bool ret = true;
	std::vector<int> vec(num_inserts);
	binary_tree<int, int> bt;

	/*  Generate vector contents randomly */
	//kp_cnt = 0;
    fill_vector_rand(vec, min_key, max_key);
	auto del_vec = vec;	
	auto expected_height = static_cast<unsigned>
		( ceil(log2(vec.size() + 1)) );
											
	/* Insert operation and associated test-cases            */
	for(auto key : vec) bt.ins(key, key);
											
	if(bt.size() != vec.size())
		cout << "Error: After insert, BT size incorrect. Expecting "
			 << vec.size() << " got " << bt.size() << endl;
	else if(bt.height() != expected_height)
		cout << "Error: After insert, BT height incorrect. Expecting "
			 << expected_height << " got " << bt.height() << endl;

	if(ret == false) goto manual_test_end;
	
	/* Delete operation and associated test-cases            */
	//std::shuffle(vec.begin(), vec.end(),
	//			 std::default_random_engine(get_rand(max_key)));
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
	//		 << vec.size() << " got " << kp_cnt << endl;
	
manual_test_end:
	if(ret == false) {
		print_table_row<int>("Input_vec", vec);
		print_table_row<int>("Del_vec", del_vec);
	}
	return ret;
}

int main()
{
	init_rand();

	bt_walkthrough();
	
	for(int i = 0; i < num_iters; ++i)
		if(bt_manual_test() == false)     exit(1);
	cout << "Info: Manual tests passed successfully" << endl;
}
