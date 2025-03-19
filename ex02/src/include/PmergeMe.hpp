#ifndef _PMERGE_HPP_
#define _PMERGE_HPP_

#include <deque>
#include <string>
#include <vector>

typedef	std::vector<int>::iterator vIter ;
typedef std::pair<int, int> intPair;

class PmergeMe
{
public:
	static bool isValidInput(std::vector<std::string>& input);
	static bool hasDuplicate(std::vector<std::string> input);

	static void vMergeInsertSort(std::vector<std::string>& input);
	static void populateVector(std::vector<std::string> input);
	static void fillSortedvPairs(void);
	static void vFillMainAndPend(void);
	static void vFillJacobsthal(void);
	static void vFillInsertion(void);
	static void vInsertInOrder(void);

	static void populateDeque(std::vector<std::string> input);

	static bool hasStraggler;
	static int	straggler;

	static std::vector<int> inputVector;
	static std::vector<std::pair<int, int> > vPairs;
	static std::vector<int> vMain;
	static std::vector<int> vPend;
	static std::vector<int> vJacobsthal;
	static std::vector<int> vInsertion;

	static std::deque<int> inputDeque;

private:
	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe(const PmergeMe& obj);
	PmergeMe& operator=(const PmergeMe& obj);
};

#endif //_PMERGE_HPP_
