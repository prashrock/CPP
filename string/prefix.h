#ifndef _PREFIX_STRING_UTILS_CPP_
#define _PREFIX_STRING_UTILS_CPP_

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
#endif //_PREFIX_STRING_UTILS_CPP_
