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

std::deque<std::pair<int, int> > PmergeMe::dPairs;
std::deque<int> PmergeMe::dMain;
std::deque<int> PmergeMe::dPend;
std::deque<int> PmergeMe::dJacobsthal;
std::deque<int> PmergeMe::dInsertion;
clock_t PmergeMe::dStart;
clock_t PmergeMe::dEnd;

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

void PmergeMe::dMergeInsertSort(std::vector<std::string>& input)
{
	PmergeMe::dStart = clock();
	populateDeque(input);
	fillSorteddPairs();
	dFillMainAndPend();
	dFillJacobsthal();
	dFillInsertion();
	dInsertInOrder();
	PmergeMe::dEnd = clock();
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

void PmergeMe::fillSorteddPairs(void)
{
	for (dIter it = inputDeque.begin(); it != inputDeque.end(); it += 2)
	{
		intPair pair(*it, *(it + 1));

		if (pair.first < pair.second)
		{
			std::swap(pair.first, pair.second);
		}
		
		dPairs.push_back(pair);
	}

	std::sort(dPairs.begin(), dPairs.end());
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

void PmergeMe::dFillMainAndPend(void)
{
	std::deque<std::pair<int, int> >::iterator it = dPairs.begin();
	std::deque<std::pair<int, int> >::iterator ite = dPairs.end();

	while (it != ite)
	{
		dMain.push_back(it->first);
		dPend.push_back(it->second);
		++it;
	}

	if (hasStraggler == true)
	{
		dPend.push_back(straggler);
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

void PmergeMe::dFillJacobsthal(void)
{
	dJacobsthal.push_back(0);
	dJacobsthal.push_back(1);

	int next = *(dJacobsthal.end() - 2) * 2 + dJacobsthal.back();

	while (next < static_cast<int>(dPend.size() - 1))
	{
		dJacobsthal.push_back(next);
		next = *(dJacobsthal.end() - 2) * 2 + dJacobsthal.back();
	}

	//delete second element to ensure uniquenesse of indexes
	dJacobsthal.erase(dJacobsthal.begin() + 1);
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

void PmergeMe::dFillInsertion(void)
{
	dInsertion.push_back(dJacobsthal.front());

	while (dInsertion.size() < dPend.size())
	{
		//erasing because we already added first element
		dJacobsthal.erase(dJacobsthal.begin());

		if (dJacobsthal.empty() == false)
		{
			int last = dInsertion.back();
			int jacob = dJacobsthal.front();

			dInsertion.push_back(jacob--);

			while (jacob > last && dInsertion.size() < dPend.size())
			{
				std::deque<int>::iterator it = dInsertion.begin();
				std::deque<int>::iterator ite = dInsertion.end();

				if (std::find(it, ite, jacob) == ite)
				{
					dInsertion.push_back(jacob);
				}

				jacob--;
			}
		}
		else 
		{
			int missing = dPend.size() - 1;

			while (dInsertion.size() < dPend.size())
			{
				dInsertion.push_back(missing--);
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

void PmergeMe::dInsertInOrder(void)
{
	std::deque<int>::iterator it = dInsertion.begin();
	std::deque<int>::iterator ite = dInsertion.end();

	while (it != ite)
	{
		int value = dPend[*it];

		std::deque<int>::iterator position = 
			std::upper_bound(dMain.begin(), dMain.end(), value);

		dMain.insert(position, value);
		++it;
	}
}

void PmergeMe::vPrint(void)
{
	std::cout << "Time to process a range of " << vMain.size() << " elements with std::Vector : " << (static_cast<float>((vEnd - vStart)) / CLOCKS_PER_SEC) * 1000000 << " us." << std::endl;
}

void PmergeMe::dPrint(void)
{
	std::cout << "Time to process a range of " << dMain.size() << " elements with std::deque : " << (static_cast<float>((dEnd - dStart)) / CLOCKS_PER_SEC) * 1000000 << " us." << std::endl;
}
