#ifndef _STRING_HELPER_UTILS_CPP_
#define _STRING_HELPER_UTILS_CPP_

/**
 * @file  String Helper
 * @brief String Helper functions
 */

/**
 * Compute the longest common prefix given 2 strings         *
 * (brute force algo).                                       *
 * @param str1                                               *
 *   First string                                            *
 * @param str2                                               *
 *   Second string                                           *
 * @return                                                   *
 *   0-based index of longest common prefix (0 if no match)  *
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
#endif //_STRING_HELPER_UTILS_CPP_
