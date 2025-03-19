#include "PmergeMe.hpp"
#include "qolMacros.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>

std::vector<int> PmergeMe::inputVector;
std::deque<int> PmergeMe::inputDeque;
bool PmergeMe::hasStraggler = false;
int PmergeMe::straggler;

std::vector<std::pair<int, int> > PmergeMe::vPairs;
std::vector<int> PmergeMe::vMain;
std::vector<int> PmergeMe::vPend;
std::vector<int> PmergeMe::vJacobsthal;
std::vector<int> PmergeMe::vInsertion;
clock_t PmergeMe::vStart;
clock_t PmergeMe::vEnd;

PmergeMe::PmergeMe(void)
{
}

PmergeMe::~PmergeMe(void)
{
}

PmergeMe::PmergeMe(const PmergeMe& obj)
{
	*this = obj;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& obj)
{
	if (this != &obj)
	{
		*this = obj;
	}

	return *this;
}

bool PmergeMe::isValidInput(std::vector<std::string>& input)
{
	std::vector<std::string>::iterator it = input.begin();
	std::vector<std::string>::iterator ite = input.end();

	while (it != ite)
	{
		std::string::iterator it2 = (*it).begin();
		std::string::iterator ite2 = (*it).end();

		while(it2 != ite2)
		{
			if (*it2 == '-')
			{
				println("Negative numbers are not supported");
				return false;
			}
			if (isdigit(*it2) == false)
			{
				println("Unexpected character detected");
				return false;
			}
			++it2;
		}
		++it;
	}

	return true;
}

bool PmergeMe::hasDuplicate(std::vector<std::string> input)
{
	std::sort(input.begin(), input.end());

	std::vector<std::string>::iterator it = input.begin();
	std::vector<std::string>::iterator ite = input.end();

	while (it != ite)
	{
		if (*it == *(it+1))
		{
			println("Sequence has duplicate element");
			return true;
		}

		++it;
	}

	return false;
}

void PmergeMe::populateDeque(std::vector<std::string> input)
{
	//capture straggler if input is odd numbered
	if (input.size() % 2 != 0)
	{
		hasStraggler = true;
		straggler = strtol(input.back().c_str(), NULL, 10);
		input.pop_back();
	}

	std::vector<std::string>::iterator it = input.begin();
	std::vector<std::string>::iterator ite = input.end();

	int number;

	while (it != ite)
	{
		number = std::strtol((*it).c_str(), NULL, 10);
		inputDeque.push_back(number);
		++it;
	}
}

void PmergeMe::vMergeInsertSort(std::vector<std::string>& input)
{
	PmergeMe::vStart = clock();
	populateVector(input);
	fillSortedvPairs();
	vFillMainAndPend();
	vFillJacobsthal();
	vFillInsertion();
	vInsertInOrder();
	PmergeMe::vEnd = clock();
}

void PmergeMe::populateVector(std::vector<std::string> input)
{
	//capture straggler if input is odd numbered
	if (input.size() % 2 != 0)
	{
		hasStraggler = true;
		straggler = std::strtol(input.back().c_str(), NULL, 10);
		input.pop_back();
	}

	std::vector<std::string>::iterator it = input.begin();
	std::vector<std::string>::iterator ite = input.end();

	int number;

	while (it != ite)
	{
		number = std::strtol((*it).c_str(), NULL, 10);
		inputVector.push_back(number);
		++it;
	}
}


void PmergeMe::fillSortedvPairs(void)
{
	for (vIter it = inputVector.begin(); it != inputVector.end(); it += 2)
	{
		intPair pair(*it, *(it + 1));

		if (pair.first < pair.second)
		{
			std::swap(pair.first, pair.second);
		}
		
		vPairs.push_back(pair);
	}

	std::sort(vPairs.begin(), vPairs.end());
}

void PmergeMe::vFillMainAndPend(void)
{
	std::vector<std::pair<int, int> >::iterator it = vPairs.begin();
	std::vector<std::pair<int, int> >::iterator ite = vPairs.end();

	while (it != ite)
	{
		vMain.push_back(it->first);
		vPend.push_back(it->second);
		++it;
	}

	if (hasStraggler == true)
	{
		vPend.push_back(straggler);
	}
}	

void PmergeMe::vFillJacobsthal(void)
{
	vJacobsthal.push_back(0);
	vJacobsthal.push_back(1);

	int next = *(vJacobsthal.end() - 2) * 2 + vJacobsthal.back();

	while (next < static_cast<int>(vPend.size() - 1))
	{
		vJacobsthal.push_back(next);
		next = *(vJacobsthal.end() - 2) * 2 + vJacobsthal.back();
	}

	//delete second element to ensure uniquenesse of indexes
	vJacobsthal.erase(vJacobsthal.begin() + 1);
}

void PmergeMe::vFillInsertion(void)
{
	vInsertion.push_back(vJacobsthal.front());

	while (vInsertion.size() < vPend.size())
	{
		//erasing because we already added first element
		vJacobsthal.erase(vJacobsthal.begin());

		if (vJacobsthal.empty() == false)
		{
			int last = vInsertion.back();
			int jacob = vJacobsthal.front();

			vInsertion.push_back(jacob--);

			while (jacob > last && vInsertion.size() < vPend.size())
			{
				std::vector<int>::iterator it = vInsertion.begin();
				std::vector<int>::iterator ite = vInsertion.end();

				if (std::find(it, ite, jacob) == ite)
				{
					vInsertion.push_back(jacob);
				}

				jacob--;
			}
		}
		else 
		{
			int missing = vPend.size() - 1;

			while (vInsertion.size() < vPend.size())
			{
				vInsertion.push_back(missing--);
			}
		}
	}
}

void PmergeMe::vInsertInOrder(void)
{
	std::vector<int>::iterator it = vInsertion.begin();
	std::vector<int>::iterator ite = vInsertion.end();

	while (it != ite)
	{
		int value = vPend[*it];

		std::vector<int>::iterator position = 
			std::upper_bound(vMain.begin(), vMain.end(), value);

		vMain.insert(position, value);
		++it;
	}
}

void PmergeMe::vPrint(void)
{
	std::cout << "Time to process a range of " << vMain.size() << " elements with std::Vector : " << (static_cast<float>((vEnd - vStart)) / CLOCKS_PER_SEC) * 1000000 << " us." << std::endl;
}
