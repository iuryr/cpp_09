#include "PmergeMe.hpp"
#include "qolMacros.hpp"
#include <vector>

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
}
