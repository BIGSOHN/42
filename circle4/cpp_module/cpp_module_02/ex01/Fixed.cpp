#include "Fixed.hpp"

Fixed::Fixed() {
	std::cout << "Default constructor called" << std::endl;
	this->rawBits = 0;
}

Fixed::Fixed(const int param) {
	std::cout << "Int constructor called" << std::endl;
	this->rawBits = param * (1 << fractionalBits);
}

Fixed::Fixed(const float param) {
	std::cout << "Float constructor called" << std::endl;
	this->rawBits = roundf(param * (1 << fractionalBits));
}

Fixed::Fixed(const Fixed& fixed) {
	std::cout << "Copy constructor called" << std::endl;
	*this = fixed;
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
	return (this->rawBits);
}

void Fixed::setRawBits(int const raw) {
	this->rawBits = raw;
}

float Fixed::toFloat(void) const {
	return ((float)this->rawBits / (1 << fractionalBits));
}

int Fixed::toInt(void) const {
	return (this->rawBits / (1 << fractionalBits));
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
    out << fixed.toFloat();
    return out;
}