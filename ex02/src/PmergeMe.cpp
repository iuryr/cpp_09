#include "PmergeMe.hpp"
#include "qolMacros.hpp"

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

bool PmergeMe::isValidInput(std::vector<std::string> input)
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
