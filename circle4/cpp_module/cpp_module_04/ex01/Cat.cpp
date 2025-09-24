#include "headers.hpp"
#include "Cat.hpp"

Cat::Cat() : Animal() {
	this->type = "Cat";
	this->brain = new Brain();
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::~Cat() {
	delete(this->brain);
	std::cout << "Cat destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	if (this != &other) {
		Animal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*(other.brain));
	}
	std::cout << "Cat assignment operator called" << std::endl;
	return *this;
}

Cat::Cat(const Cat& other) : Animal(other) {
	this->brain = new Brain(*(other.brain));
	std::cout << "Cat copy constructor called" << std::endl;
}

void Cat::makeSound() const {
	std::cout << "Meow!" << std::endl;
}

Brain* Cat::getBrain() const {
	return (this->brain);
}