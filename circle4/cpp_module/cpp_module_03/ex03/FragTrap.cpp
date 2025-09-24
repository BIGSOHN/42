#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;

	std::cout << "FragTrap " << this->name << " called" << std::endl;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	this->hitPoints = 100;
	this->energyPoints = 100;
	this->attackDamage = 30;

	std::cout << "FragTrap " << this->name << " called" << std::endl;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap " << this->name << " dead" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

FragTrap::FragTrap(const FragTrap& fragTrap) : ClapTrap(fragTrap) {

}

void FragTrap::attack(const std::string& target) {
	if (this->energyPoints > 0 && hitPoints > 0) {
		std::cout << "FragTrap " << this->name << " attacks " << target \
		<< ", causing " << this->attackDamage << " points of damage!" << std::endl;
		this->energyPoints--;
	}
	else {
		std::cout << "FragTrap " << this->name << " can't attack" << std::endl;
	}
}

void FragTrap::highFivesGuys(void) {
	if (this->hitPoints > 0) {
		std::cout << this->name << " requests a positive high-fives." << std::endl;
	}
	else {
		std::cout << this->name << " can't request a positive high-fives." << std::endl;
	}
}
