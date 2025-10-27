#include "headers.hpp"
#include "Span.hpp"

Span::Span() : _maxSize(0), _numbers() {

}
Span::Span(unsigned int size) : _maxSize(size), _numbers() {
	// reserve - 공간만, 값 없음 .size() 연산지 0이 나옴
	_numbers.reserve(size);
	// _numbers(size) - 생성자 초기화 - N개 요소 생성 .size() 연산시 N개가 나옴
}
Span::Span(const Span& other) : _maxSize(other._maxSize), _numbers(other._numbers) {
	// vector 자체의 복사 생성자가 있어서 알아서 복사됨
}
Span& Span::operator=(const Span& other) {
	if (this != &other) {
		this->_maxSize = other._maxSize;
		this->_numbers = other._numbers;
	}
	return *this;
}
Span::~Span() {

}

void Span::addNumber(int number) {
	if (_numbers.size() >= _maxSize) {
		throw std::exception();
	}
	_numbers.push_back(number);
}
unsigned int Span::shortestSpan() {
	if (_numbers.size() < 2) {
		throw std::exception();
	}
	std::sort(_numbers.begin(), _numbers.end());
	unsigned int minSpan = _numbers[1] - _numbers[0];
	for (size_t i = 2; i < _numbers.size(); i++) {
		unsigned span = _numbers[i] - _numbers[i - 1];
		if (span < minSpan) {
			minSpan = span;
		}
	}
	return minSpan;
	
}
unsigned int Span::longestSpan() {
	if (_numbers.size() < 2) {
		throw std::exception();
	}
	std::sort(_numbers.begin(), _numbers.end());
	return (_numbers.back() - _numbers.front());
}