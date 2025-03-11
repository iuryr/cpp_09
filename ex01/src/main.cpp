#include "qolMacros.hpp"
#include "RPN.hpp"

int main(int argc, char** argv)
{
	(void) argv;
	if (argc != 2)
	{
		println("Usage: ./RPN expression_in_reverse_polish_notation");
		println("Obs 1: leading and trailing whitespaces are ignored");
		println("Obs 2: multiple whitespaces between elements not allowed");
		return 1;
	}

	std::string input(argv[1]);
	if (input.empty() == true)
	{
		println("Error");
		return 1;
	}

	if (RPN::process(input) == 1)
	{
		return 1;
	}
	return 0;
}
