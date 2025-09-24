#ifndef DOG_HPP
# define DOG_HPP

#include "headers.hpp"
#include "classes.hpp"

class Dog : public Animal {
private:
	
public:
	Dog();
	~Dog();
	Dog& operator=(const Dog& other); 
	Dog(const Dog& other);

	virtual void makeSound() const;
};

#endif