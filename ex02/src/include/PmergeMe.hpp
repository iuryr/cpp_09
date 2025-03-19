#ifndef _PMERGE_HPP_
#define _PMERGE_HPP_

#include <deque>
#include <string>
#include <vector>
#include <list>
#include <ctime>

typedef	std::vector<int>::iterator vIter ;
typedef	std::deque<int>::iterator dIter ;
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
	static void vPrint(void);

	static void dMergeInsertSort(std::vector<std::string>& input);
	static void populateDeque(std::vector<std::string> input);
	static void fillSorteddPairs(void);
	static void dFillMainAndPend(void);
	static void dFillJacobsthal(void);
	static void dFillInsertion(void);
	static void dInsertInOrder(void);
	static void dPrint(void);

	static bool hasStraggler;
	static int	straggler;

	static std::vector<int> inputVector;
	static std::vector<std::pair<int, int> > vPairs;
	static std::vector<int> vMain;
	static std::vector<int> vPend;
	static std::vector<int> vJacobsthal;
	static std::vector<int> vInsertion;
	static clock_t vStart;
	static clock_t vEnd;

	static std::deque<int> inputDeque;
	static std::deque<std::pair<int, int> > dPairs;
	static std::deque<int> dMain;
	static std::deque<int> dPend;
	static std::deque<int> dJacobsthal;
	static std::deque<int> dInsertion;
	static clock_t dStart;
	static clock_t dEnd;

private:
	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe(const PmergeMe& obj);
	PmergeMe& operator=(const PmergeMe& obj);
};

#endif //_PMERGE_HPP_
