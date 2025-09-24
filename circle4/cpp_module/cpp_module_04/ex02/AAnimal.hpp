#ifndef AANIMAL_HPP
# define AANIMAL_HPP

#include "headers.hpp"

class AAnimal
{
private:

protected:
	std::string type;

public:
	AAnimal();
	virtual ~AAnimal();
	AAnimal& operator=(const AAnimal& other);
	AAnimal(const AAnimal& other);

	virtual void makeSound() const = 0;
	std::string getType() const;
};

#endif