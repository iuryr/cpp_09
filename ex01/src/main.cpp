#include "qolMacros.hpp"
#include "RPN.hpp"

int main(int argc, char** argv)
{
	(void) argv;
	if (argc != 2)
	{
		println("Usage: ./RPN expression_in_reverse_polish_notation");
		return 1;
	}

	std::string input(argv[1]);

	if (RPN::process(input) == 1)
	{
		return 1;
	}
	return 0;
}
