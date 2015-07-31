#include <iostream>          /* std::cout                    */
#include <fstream>           /* std::ifstream                */
#include <sstream>           /* std::istringstream           */
#include <cstring>           /* strtok                       */
#include <iomanip>           /* std::setw                    */
#include <cmath>             /* pow                          */
#include <cassert>           /* assert                       */
#include <algorithm>         /* std::max                     */
#include <string>            /* std::string                  */
#include <map>               /* std::map container           */
using namespace std;

//https://github.com/thanthese/count-word-frequencies/blob/master/wordsInAFile.py

bool second_comp(const pair<string, int> &a, const pair<string, int> &b)
{
	return a.second < b.second;
}

void word_counter(const char *filename, int max_cnt)
{
	ifstream instream;
	string line;
	std::string word;
	std::map<std::string, int> word_map;
	/* Input stream should have only letters                 */
	instream.imbue(std::locale());
	instream.open(filename);
	while(instream >> word)
		++word_map[word];
	/* Iterate over the map DS and print the top words       */
	for(auto it = word_map.cbegin(); it != word_map.cend() && max_cnt--; ++it)
	{
		cout << it->first << " : " << it->second << endl;
	}
	instream.close();
}

int main(int argc, char *argv[])
{
	if(argc != 3) {
		cerr << "Usage: " << argv[0] << " <file_name> <max_words>"
			 << endl;
		return -1;
	}
	word_counter(argv[1], atoi(argv[2]));
	return 0;
}

