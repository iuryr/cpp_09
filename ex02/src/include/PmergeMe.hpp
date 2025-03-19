#ifndef _PMERGE_HPP_
#define _PMERGE_HPP_

#include <string>

class PmergeMe
{
public:
	static bool hasNegative(std::string& input);
	static bool hasDuplicate(std::string& input);

private:
	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe(const PmergeMe& obj);
	PmergeMe& operator=(const PmergeMe& obj);
};

#endif //_PMERGE_HPP_
