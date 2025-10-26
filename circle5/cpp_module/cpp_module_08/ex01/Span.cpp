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

}
unsigned int Span::shortestSpan() {

}
unsigned int Span::longestSpan() {

}