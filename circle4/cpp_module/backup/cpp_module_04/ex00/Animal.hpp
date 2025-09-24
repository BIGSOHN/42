#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include "headers.hpp"
#include "classes.hpp"

class Animal
{
private:
	/* data */

protected:
	std::string type;

public:
	Animal(/* args */);
	~Animal();
	Animal& operator=(const Animal& other);
	Animal(const Animal& animal);
};

#endif