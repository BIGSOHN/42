template<typename Iterator>
void Span::addNumbers(Iterator begin, Iterator end) {
	size_t count = std::distance(begin, end);
	if (_numbers.size() + count > _maxSize) {
		throw std::exception();
	}
	_numbers.insert(_numbers.end(), begin, end);
}