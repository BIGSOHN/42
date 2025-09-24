#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private:
	int rawBits;
	static const int fractionalBits = 8;
public:
	Fixed();
	Fixed(const int param);
	Fixed(const float param);
	Fixed(const Fixed& fixed);
	Fixed& operator = (const Fixed& rhs);
	~Fixed();
	int getRawBits() const;
	void setRawBits(int const raw);
	float toFloat( void ) const;
	int toInt( void ) const;
};

std::ostream& operator<<(std::ostream& out, const Fixed& fixed);

#endif