#include "PmergeMe.hpp"
#include "qolMacros.hpp"
#include <algorithm>
#include <cstdlib>

std::vector<int> PmergeMe::inputVector;
std::deque<int> PmergeMe::inputDeque;
bool PmergeMe::hasStraggler = false;
int PmergeMe::straggler;

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

void PmergeMe::populateContainers(std::vector<std::string> input)
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
		inputVector.push_back(number);
		++it;
	}
}
