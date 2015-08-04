#ifndef _SUBSTRING_UTILS_CPP_
#define _SUBSTRING_UTILS_CPP_

/* Naive method:                                             *
 * For every position in text, consider it as a starting     *
 * position for pattern and see if there is a match.         *
 * Time Complexity = O(nm)                                   *
 * Issues:                                                   *
 * Backup - this algo needs backtrack for every mismatch     *
 * This is a problem when dealing with streams               */
template<typename T=std::string>
static inline int substring_brute(T text, T pattern)
{
	if(text.empty() || pattern.empty()) return -1;
	for(int i = 0; i <= text.size() - pattern.size(); ++i)
	{
		int j;
		for(j = 0; j < pattern.size() && i + j < text.size(); ++j) 
			if(text[i + j] != pattern[j]) break;
		
		if(j == pattern.size()) return i;
	}
	return -1;
}

/* Optimized Naive method:                                   *
 * Use one for-loop to iterate over the text and backup text *
 * explicitly everytime there is a mismatch (rewind pattern  *
 * as well).                                                 *
 * Worst Case Time Complexity = O(nm)                        */
template<typename T=std::string>
static inline int substring_opt(T text, T pattern)
{
	int i, j;
	if(text.empty() || pattern.empty()) return -1;
	for(i = 0, j = 0; i < text.size() && j < pattern.size(); ++i)
	{
		if(text[i] == pattern[j])      j++;
		/* if mismatch, backtrack text by j and reset pattern*/
		else {
			i -= j;
			j = 0;
		}
	}
	if(j == pattern.size())   return (i - pattern.size());
	else                      return -1;
}

/* Knuth Morris Pratt (KMP) Algorithm:                       *
 * Advantages:                                               *
 * - No text backtrack needed (supports input text stream)   *
 */
	
/* Compute the length of the longest common prefix given     *
 * two strings.                                              *
 * @param str1  - First string                               *
 * @param str2  - Second string                              *
 * Time Complexity = O(n) where n=len of longest comm prefix *
 * Space Complexity= O(1)                                    *
 * Note: Linear time worst case, sublinear time typical case */
template<typename T=std::string>
static inline int longest_prefix_brute(T str1, T str2)
{
	/* Stop till the length of the smallest string           */
	size_t n = std::min(str1.size(), str2.size());
	/* Iterate from start till two strings dont match        */
	for(int i = 0; i < n; ++i)
		if(str1[i] != str2[i])
			return i;
	return n;
}
#endif //_SUBSTRING_UTILS_CPP_
