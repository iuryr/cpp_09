#ifndef _PMERGE_HPP_
#define _PMERGE_HPP_

#include <deque>
#include <string>
#include <vector>

class PmergeMe
{
public:
	static bool isValidInput(std::vector<std::string>& input);
	static bool hasDuplicate(std::vector<std::string> input);
	static void populateContainers(std::vector<std::string> input);

	static std::vector<int> inputVector;
	static std::deque<int> inputDeque;
	static bool hasStraggler;
	static int	straggler;

private:
	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe(const PmergeMe& obj);
	PmergeMe& operator=(const PmergeMe& obj);
};

#endif //_PMERGE_HPP_
