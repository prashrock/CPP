#include <iostream>            /* std::cout                  */
#include <vector>              /* std::vector                */
#include <cmath>               /* pow                        */
#include <cassert>             /* assert                     */
#include <algorithm>           /* std::max                   */

#include "rand_generator.h"    /* init_rand()                */
#include "rway_trie.h"         /* R-Way Trie API             */
using namespace std;

const int num_inserts = 10;

int main()
{
	int val = 19;
	init_rand();
	//vector<int> key(2);
	//key[0] = 0; key[1] = 1;
	//rw_trie::rway_trie<vector<int>, int, 2> tr;
	//tr.put(key, val); val = 0;
	//cout << "num children = " << tr.calc_size() << endl;
	//if(tr.get(key, val))
	//	cout  << "found, val = " << val << endl;
	rw_trie::rway_trie<string, int> tr;
	val = 1;  tr.put("a",  val);
	val = 2;  tr.put("aa",  val);
	val = 3;  tr.put("aaa",  val);
	val = 4123;  tr.put("aaa", val);
	val = 0;
	//cout << "num children = " << tr.calc_size() << endl;
	if(tr.del("a") == false) cout << "a del error" << endl; 
	if(tr.get("aaa", val))
		cout  << "found aaa, val = " << val << endl;
	else
		cout << "aaa not found" << endl;
	if(tr.get("aa", val))
		cout  << "found aa, val = " << val << endl;
	else
		cout << "aa not found" << endl;

	if(tr.del("aaa") == false) cout << "aaa del error" << endl;
	if(tr.del("aa") == false) cout << "aa del error" << endl;
	if(tr.del("a") == true) cout << "a del error" << endl;

	return 0;
}

