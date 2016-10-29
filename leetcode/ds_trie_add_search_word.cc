//g++-5 --std=c++11 -Wall -g -o ds_trie_add_search_word ds_trie_add_search_word.cc

/**
 * @file  Add/Search word Data Structure
 * @brief DS to add and search words
 */

// https://leetcode.com/problems/add-and-search-word-data-structure-design/

#include <iostream>          /* std::cout                    */
#include <algorithm>         /* std::max                     */
#include <vector>            /* std::vector                  */
#include <string>            /* std::string,                 */
using namespace std;

/**
 * Design a data structure that supports the following two operations:
 * void addWord(word)
 * bool search(word)
 * search(word) can search a literal word or a regular expression string
 * containing only letters a-z or .. A . means it can represent any one letter.
 * For example:
 *     addWord("bad")
 *     addWord("dad")
 *     addWord("mad")
 *     search("pad") -> false
 *     search("bad") -> true
 *     search(".ad") -> true
 *     search("b..") -> true
 *  Note: You may assume that all words are consist of lowercase letters a-z.
 */

class RW_TrieNode {
public:
   bool isKey;
   RW_TrieNode(): isKey(false), next(26, nullptr) { }
   std::vector<RW_TrieNode *> next;
};

RW_TrieNode *root;

// Adds a word into the data structure.
void addWord(string word) {
   RW_TrieNode *cur = root;
   for(auto c : word) {
      int idx = c - 'a';
      if(cur->next[idx] == nullptr) cur->next[idx] = new RW_TrieNode();
      cur = cur->next[idx];
   }
   cur->isKey = true;
}

bool search_help(string word, RW_TrieNode *root) {
   RW_TrieNode *cur = root;
   for(int i = 0; i < (int)word.size(); ++i) {
      if(cur == nullptr) return false;
      else if(word[i] == '.') {
         for(int j = 0; j < 26; ++j) {
            if(search_help(word.substr(i + 1), cur->next[j])) return true;
         }
         return false;
      }
      else cur = cur->next[word[i] - 'a'];
   }
   return cur && cur->isKey;
}

// Returns if the word is in the data structure. A word could
// contain the dot character '.' to represent any one letter.
bool search(string word) {
   return search_help(word, root);
}

/* Note: there is a memory leak as RWay Trie nodes are not freed */
int main()
{
   { /* Try doing a search without an add */
      root = new RW_TrieNode();
      if(search("a") != false)  return -1;
   }
   { /* Add 3 elements and try 4 searches */
      root = new RW_TrieNode();
      addWord("bad");
      addWord("dad");
      addWord("mad");
      if(search("pad") != false) return -2;
      if(search("bad") != true)  return -3;
      if(search(".ad") != true)  return -4;
      if(search("b..") != true)  return -5;
   }
   
   //addWord("ran"),addWord("rune"),addWord("runner"),addWord("runs"),addWord("add"),addWord("adds"),addWord("adder"),addWord("addee"),search("r.n"),search("ru.n.e"),search("add"),search("add."),search("adde."),search(".an."),search("...s"),search("....e."),search("......."),search("..n.r")
   cout << "Info: All manual test-cases passed." << endl;
   return 0;
}
