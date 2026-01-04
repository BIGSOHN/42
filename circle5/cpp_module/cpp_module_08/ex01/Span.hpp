#ifndef SPAN_HPP
# define SPAN_HPP

#include "headers.hpp"

class Span {
	private:
		unsigned int _maxSize;
		std::vector<int> _numbers;

	public:
		Span();
		Span(unsigned int size);
		Span(const Span& other);
		Span& operator=(const Span& other);
		~Span();

		void addNumber(int number);
		unsigned int shortestSpan();
		unsigned int longestSpan();

		template<typename Iterator>
		void addNumbers(Iterator begin, Iterator end);
};

#include "Span.tpp"

#endif