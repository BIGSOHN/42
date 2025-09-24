#include "Fixed.hpp"

Fixed::Fixed() {
	std::cout << "Default constructor called" << std::endl;
	this->rawBits = 0;
}

Fixed::Fixed(const Fixed& fixed) : Fixed() {
	std::cout << "Copy constructor called" << std::endl;
	// *this = fixed;
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called " << std::endl;
	if (this != &other) {
		this->setRawBits(other.getRawBits());
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}


int Fixed::getRawBits() const {
	std::cout << "getRawBits member function called" << std::endl;
	return (this->rawBits);
}

void Fixed::setRawBits(int const raw) {
	this->rawBits = raw;
}