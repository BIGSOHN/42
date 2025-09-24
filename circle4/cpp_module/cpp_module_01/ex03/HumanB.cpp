#include "headers.hpp"
#include "classes.hpp"

HumanB::HumanB() {

}

HumanB::HumanB(std::string name) {
	this->name = name;
}

HumanB::~HumanB() {

}

void	HumanB::attack() {
	if (this->weapon != NULL)
		std::cout << this->name << " attacks with their " << this->weapon->getType() << std::endl;
	else
		std::cout << this->name << " does not have a weapon" << std::endl;
}

void	HumanB::setWeapon(Weapon& weapon) {
	this->weapon = &weapon;
}