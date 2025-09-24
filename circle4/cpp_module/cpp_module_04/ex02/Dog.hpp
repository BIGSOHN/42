#ifndef DOG_HPP
# define DOG_HPP

#include "headers.hpp"
#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
private:
	Brain* brain;
	
public:
	Dog();
	~Dog();
	Dog& operator=(const Dog& other); 
	Dog(const Dog& other);

	virtual void makeSound() const;
	Brain* getBrain() const;
};

#endif