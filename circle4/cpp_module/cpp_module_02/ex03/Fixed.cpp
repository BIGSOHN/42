#include "Fixed.hpp"

Fixed::Fixed() {
	this->rawBits = 0;
}

Fixed::~Fixed() {
}

Fixed::Fixed(const int param) {
	this->rawBits = param * (1 << fractionalBits);
}

Fixed::Fixed(const float param) {
	this->rawBits = roundf(param * (1 << fractionalBits));
}

Fixed::Fixed(const Fixed& fixed) {
	*this = fixed;
}

Fixed& Fixed::operator=(const Fixed& other) {
	if (this != &other) {
		this->setRawBits(other.getRawBits());
	}
	return *this;
}

Fixed Fixed::operator+(const Fixed& rhs) {
	return Fixed(rawBits + rhs.rawBits);
}

Fixed Fixed::operator-(const Fixed& rhs) {
	return Fixed(rawBits - rhs.rawBits);
}

Fixed Fixed::operator*(const Fixed& rhs) {
	return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(const Fixed& rhs) {
	return Fixed(rawBits / rhs.rawBits);
}

bool Fixed::operator>(const Fixed& rhs) {
	return (rawBits > rhs.rawBits);
}

bool Fixed::operator<(const Fixed& rhs) {
	return (rawBits < rhs.rawBits);
}

bool Fixed::operator>=(const Fixed& rhs) {
	return (rawBits >= rhs.rawBits);
}

bool Fixed::operator<=(const Fixed& rhs) {
	return (rawBits <= rhs.rawBits);
}

bool Fixed::operator==(const Fixed& rhs) {
	return (rawBits == rhs.rawBits);
}

bool Fixed::operator!=(const Fixed& rhs) {
	return (rawBits != rhs.rawBits);
}

Fixed& Fixed::operator++() {
	rawBits++;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed temp = *this;
	rawBits++;
	return (temp);
}

Fixed& Fixed::operator--() {
	rawBits--;
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed temp = *this;
	rawBits--;
	return (temp);
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
	if (a < b) {
		return a;
	}
	return b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
	if (a.getRawBits()  < b.getRawBits()) {
		return a;
	}
	return b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
	if (a > b) {
		return a;
	}
	return b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	if (a.getRawBits() > b.getRawBits()) {
		return a;
	}
	return b;
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