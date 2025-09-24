#include "headers.hpp"
#include "Zombie.hpp"

Zombie::Zombie() {
}

Zombie::Zombie(std::string name) {
	this->name = name;
}

Zombie::~Zombie() {
	std::cout << this->name << " is died" << std::endl;
}

void Zombie::announce() {
	std::cout << this->name << ": Moar brainz!" << std::endl;
}

void	Zombie::setName(std::string name) {
	this->name = name;
}

