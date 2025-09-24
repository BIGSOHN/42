#include "ClapTrap.hpp"

ClapTrap::ClapTrap() {
	this->name = "Default";
	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 0;

	std::cout << "ClapTrap " << this->name << " called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) {
	this->name = name;
	this->hitPoints = 10;
	this->energyPoints = 10;
	this->attackDamage = 0;

	std::cout << "ClapTrap " << this->name << " called" << std::endl;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap " << this->name << " dead" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
	if (this != &other) {
		this->name = other.name;
		this->hitPoints = other.hitPoints;
		this->energyPoints = other.energyPoints;
		this->attackDamage = other.attackDamage;
	}
	return *this;
}

ClapTrap::ClapTrap(const ClapTrap& clapTrap) {
	*this = clapTrap;
}

void ClapTrap::attack(const std::string& target) {
	if (this->energyPoints > 0 && hitPoints > 0) {
		std::cout << "ClapTrap " << this->name << " attacks " << target \
		<< ", causing " << this->attackDamage << " points of damage!" << std::endl;
		this->energyPoints--;
	}
	else {
		std::cout << "ClapTrap " << this->name << " can't attack" << std::endl;
	}
}

void ClapTrap::takeDamage(unsigned int amount) {
	std::cout << this->name << " takes " << amount << " damage" << std::endl;
	if (hitPoints > amount) {
		this->hitPoints -= amount;
		this->energyPoints -= 1;;
		std::cout << this->name << " has " << this->hitPoints << " hit points" << std::endl;
	}
	else {
		this->hitPoints = 0;
		std::cout << this->name << " fell down" << std::endl;
	}
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (this->hitPoints > 0 && energyPoints > 0) {
		this->hitPoints += amount;
		this->energyPoints -= 1;
		std::cout << this->name << " is repaired " << amount << " points" << std::endl;
		std::cout << this->name << " has " << this->hitPoints << " hit points" << std::endl;
	}
	else {
		std::cout << this->name << " can not be repaired" << std::endl;
	}
}