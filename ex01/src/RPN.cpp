#include "RPN.hpp"

std::stack<std::string> RPN::_opElements;

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

void RPN::fillStack(std::string& input)
{
	std::string sep(" ");
	std::string token;

	size_t found = input.rfind(sep);
	while (found != std::string::npos)
	{
		if (found == input.length() - 1)
		{
			input = input.substr(0, found);
			found = input.rfind(sep);
			continue;
		}

		token = input.substr(found + 1);
		RPN::_opElements.push(token);

		input = input.substr(0, found);
		found = input.rfind(sep);
	}

	if (input.empty() == false)
	{
		RPN::_opElements.push(input);
	}
}
