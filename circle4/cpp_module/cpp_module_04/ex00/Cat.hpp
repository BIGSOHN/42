#ifndef CAT_HPP
# define CAT_HPP

#include "headers.hpp"
#include "classes.hpp"

class Cat : public Animal {
private:
	
public:
	Cat();
	~Cat();
	Cat& operator=(const Cat& other);
	Cat(const Cat& other);

	virtual void makeSound() const;
};

#endif