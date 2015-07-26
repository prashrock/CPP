#ifndef _SUBSTRING_UTILS_CPP_
#define _SUBSTRING_UTILS_CPP_

/* Naive method:                                             *
 * For every position in text, consider it as a starting     *
 * position for pattern and see if there is a match.         *
 * Time Complexity = O(nm)                                   */
template<typename T=std::string>
static inline int substring_brute(T text, T pattern)
{
	if(text.empty() || pattern.empty()) return -1;
	for(int i = 0; i < text.size(); ++i)
	{
		int j;
		for(j = 0; j < pattern.size() && i + j < text.size(); ++j) 
			if(text[i + j] != pattern[j]) break;
		
		if(j == pattern.size()) return i;
	}
	return -1;
}

/* Optimized Naive method:                                   *
 * For every position in text, consider it as a starting     *
 * position for pattern and see if there is a match.         *
 * Worst Case Time Complexity = O(nm)                        */
template<typename T=std::string>
static inline int substring_opt(T text, T pattern)
{
	int i, j;
	if(text.empty() || pattern.empty()) return -1;
	for(i = 0, j = 0; i < text.size(); ++i)
	{
		if(j == pattern.size()) {
			break;
		}
		if(text[i] == pattern[j])      j++;
		else {
			i -= j;
			j = 0;
		}
	}

	if(j == pattern.size()) {
		return (i - pattern.size());
	}

	return -1;
}

#endif //_SUBSTRING_UTILS_CPP_
