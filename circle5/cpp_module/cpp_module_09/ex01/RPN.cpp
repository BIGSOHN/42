#include "RPN.hpp"

RPN::RPN() {

}
RPN::RPN(const RPN& other) : _stack(other._stack) {

}
RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}
RPN::~RPN() {

}

bool RPN::isOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

double RPN::calculate(double a, double b, char op) {
	if (op == '+') {
		return a + b;
	} else if (op == '-') {
		return a - b;
	} else if (op == '*') {
		return a * b;
	} else {
		return a / b;
	}
}

void RPN::execute(const std::string& expression) {
	std::stringstream ss(expression);
	std::string token;

	while (ss >> token) {
		if (token.length() == 1) {
			if (isdigit(token[0])) {
				_stack.push(atoi(token.c_str()));
			} else if (isOperator(token[0])) {
				// stack에 숫자가 2개 미만일 때
				if (_stack.size() < 2) {
					std::cerr << "Error" << std::endl;
					return;
				}
				double b = _stack.top();
				_stack.pop();
				double a = _stack.top();
				_stack.pop();
				// b가 0이고 나누기를 시도할 경우에 에러.
				if (token[0] == '/' && b == 0) {
					std::cerr << "Error" << std::endl;
					return;
				}
				_stack.push(calculate(a, b, token[0]));
			} else {
				std::cerr << "Error" << std::endl;
				return;
			}
		} else {
			std::cerr << "Error" << std::endl;
			return;
		}
	}

	if (_stack.size() != 1) {
		std::cerr << "Error" << std::endl;
		return;
	}
	std::cout << _stack.top() << std::endl;
}