#ifndef WRONGANIMAL_HPP
# define WRONGANIMAL_HPP

#include "headers.hpp"
#include "classes.hpp"

class WrongAnimal
{
private:

protected:
	std::string type;

public:
	WrongAnimal();
	virtual ~WrongAnimal();
	WrongAnimal& operator=(const WrongAnimal& other);
	WrongAnimal(const WrongAnimal& other);

	void makeSound() const;
	std::string getType() const;
};

#endif