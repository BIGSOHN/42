#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include "headers.hpp"
#include "classes.hpp"

class Animal
{
private:

protected:
	std::string type;

public:
	Animal();
	virtual ~Animal();
	Animal& operator=(const Animal& other);
	Animal(const Animal& other);

	virtual void makeSound() const;
	std::string getType() const;
};

#endif