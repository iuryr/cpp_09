#include "PmergeMe.hpp"
#include "qolMacros.hpp"

void printBefore(std::vector<std::string> input)
{
	std::vector<std::string>::iterator it = input.begin();
	std::vector<std::string>::iterator ite = input.end();

	std::cout << "Before: ";

	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

void printAfter(void)
{
	std::deque<int>::iterator it = PmergeMe::dMain.begin();
	std::deque<int>::iterator ite = PmergeMe::dMain.end();

	std::cout << "After: ";

	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
}

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		println("Usage: ./PmergeMe positive_number [positive_number]...");
		return 1;
	}

	std::vector<std::string> input;
	++argv;
	while(*argv != NULL)
	{
		input.push_back(*argv);
		++argv;
	}

	if (PmergeMe::isValidInput(input) == false)
	{
		return 1;
	}

	if (PmergeMe::hasDuplicate(input) == true)
	{
		return 1;
	}

	printBefore(input);
	PmergeMe::vMergeInsertSort(input);
	PmergeMe::dMergeInsertSort(input);
	printAfter();
	PmergeMe::vPrint();
	PmergeMe::dPrint();
}
