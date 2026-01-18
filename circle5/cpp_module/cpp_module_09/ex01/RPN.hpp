#ifndef RPN_HPP
#define RPN_HPP

#include "headers.hpp"

class RPN {
private:
	std::stack<double> _stack;

	bool isOperator(char c);
	double calculate(int a, int b, char op);

public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	void execute(const std::string& expression);
};


#endif

