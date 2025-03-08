#include "RPN.hpp"
#include "qolMacros.hpp"
#include <cctype>

static bool isOperatorSymbol(char c);

std::stack<int> RPN::_opElements;

RPN::RPN(void)
{
};

RPN::~RPN(void)
{
};

RPN::RPN(const RPN& obj)
{
	*this = obj;
}

RPN& RPN::operator=(const RPN& obj)
{
	(void) obj;
	return *this;
}

int RPN::process(std::string& input)
{
	//ignore leading whitespaces
	size_t firstNonWSChar = input.find_first_not_of(" ");
	if (firstNonWSChar != std::string::npos)
	{
		input = input.substr(firstNonWSChar);
	}
	else
	{
		input.clear();
		return 1;
	}

	//ignore trailing whitespaces
	size_t lastNonWSChar = input.find_last_not_of(" ");
	if (lastNonWSChar != std::string::npos)
	{
		input.erase(lastNonWSChar + 1);
	}
	else 
	{
		input.clear();
		return 1;
	}


	return 0;
}

static bool isOperatorSymbol(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return true;
	return false;
}
