#include "headers.hpp"
#include "AAnimal.hpp"

AAnimal::AAnimal() : type("") {
	std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::~AAnimal() {
	std::cout << "AAnimal destructor called" << std::endl;
}

AAnimal& AAnimal::operator=(const AAnimal& other) {
	if (this != &other) {
		this->type = other.type;
	}
	std::cout << "AAnimal assignment operator called" << std::endl;
	return *this;
}

AAnimal::AAnimal(const AAnimal& other) : type(other.type) {
	std::cout << "AAnimal copy constructor called" << std::endl;
	*this = other;
}

std::string AAnimal::getType() const {
	return (this->type);
}