#ifndef _RPN_HPP_
#define _RPN_HPP_

#include <stack>
#include <string>

class RPN
{
public:
	static int process(std::string& input);
	static int eval(std::stack<int>& stack, char opSymbol);

private:
	RPN(void);
	~RPN(void);
	RPN(const RPN& obj);
	RPN& operator=(const RPN& obj);

	static std::stack<int> _opElements;
};

#endif //_RPN_HPP_
