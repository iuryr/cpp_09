#include "RPN.hpp"
#include "qolMacros.hpp"
#include <cctype>
#include <cstdlib>

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

	//input has only one element
	size_t found = input.find(" ");
	if (found == std::string::npos)
	{
		println("Error");
		return 1;
	}

	while (found != std::string::npos || input.length() != 0)
	{
		std::string token = input.substr(0, input.find(" "));

		//fail whenever 2character token (negative or >10 numbers) 
		if (token.length() != 1)
		{
			println("Error");
			return 1;
		}

		//if is number, add to stack
		if (isdigit(token[0]) != false)
		{
			_opElements.push(atoi(token.c_str()));
			if (found != std::string::npos)
			{
				input = input.substr(found + 1);
			}
			else
			{
				input.clear();
			}
			found = input.find(" ");
			continue;
		}

		//if is opSymbol, perform evaluation and push to stack
		int evalStatus;
		if (isOperatorSymbol(token[0]) == true)
		{
			switch (token[0])
			{
				case '+':
					evalStatus = eval(_opElements, token[0]);
					break;
				case '-':
					evalStatus = eval(_opElements, token[0]);
					break;
				case '*':
					evalStatus = eval(_opElements, token[0]);
					break;
				case '/':
					evalStatus = eval(_opElements, token[0]);
					break;
			}
			
			if (evalStatus == 1)
			{
				println("Error");
				return 1;
			}
			else
			{
				if (found != std::string::npos)
				{
					input = input.substr(found + 1);
				}
				else
				{
					input.clear();
				}
				found = input.find(" ");
				continue;
			}
		}
	}

	if (_opElements.size() != 1)
	{
		println("Error");
		return 1;
	}

	println(_opElements.top());
	return 0;
}

static bool isOperatorSymbol(char c)
{
	if (c == '+' || c == '-' || c == '/' || c == '*')
		return true;
	return false;
}

int RPN::eval(std::stack<int>& stack, char opSymbol)
{
	int firstOperand;
	int secondOperand;
	int result;

	if (stack.size() >= 1)
	{
		secondOperand = stack.top();
		stack.pop();
	}
	else
	{
		return 1;
	}

	if (stack.size() >= 1)
	{
		firstOperand = stack.top();
		stack.pop();
	}
	else
	{
		return 1;
	}

	switch (opSymbol)
	{
		case '+':
			result = firstOperand + secondOperand;
			break;
		case '-':
			result = firstOperand - secondOperand;
			break;
		case '*':
			result = firstOperand * secondOperand;
			break;
		case '/':
			if (secondOperand == 0)
				return 1;
			result = firstOperand / secondOperand;
			break;
	}
	stack.push(result);
	return 0;
}
