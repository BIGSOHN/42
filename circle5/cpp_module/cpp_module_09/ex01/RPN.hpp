#ifndef RPN_HPP
#define RPN_HPP

#include "headers.hpp"

class RPN {
private:
	std::stack<int> _stack;

	bool isOperator(char c);
	int calculate(int a, int b, char op);

public:
	RPN();
	RPN(RPN& other);
	RPN& operator=(RPN& other);
	~RPN();

	int evaluate(const std::string& expression);
};


#endif

