#include "headers.hpp"
#include "Dog.hpp"

Dog::Dog() : AAnimal() {
	this->type = "Dog";
	this->brain = new Brain();
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::~Dog() {
	delete(this->brain);
	std::cout << "Dog destructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	if (this != &other) {
		AAnimal::operator=(other);
		delete this->brain;
		this->brain = new Brain(*(other.brain));
	}
	std::cout << "Dog assignment operator called" << std::endl;
	return *this;
}

Dog::Dog(const Dog& other) : AAnimal(other) {
	this->brain = new Brain(*(other.brain));
	std::cout << "Dog copy constructor called" << std::endl;
}

void Dog::makeSound() const {
	std::cout << "Bark!" << std::endl;
}

Brain* Dog::getBrain() const {
	return (this->brain);
}