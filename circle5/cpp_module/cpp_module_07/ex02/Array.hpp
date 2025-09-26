#ifndef ARRAY_HPP
# define ARRAY_HPP

#include "headers.hpp"

template <typename T>
class Array {
private:
	T* _elements;
	unsigned _size;
public:
	Array();
	Array(unsigned int n);
	~Array();
	Array(const Array& other);
	Array& operator=(const Array& other);

	T& operator[](unsigned int index);
	const T& operator[](unsigned int index) const;
	unsigned int size() const;
};


#include "Array.tpp"

#endif