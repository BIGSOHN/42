#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	this->gateKeeperMode = false;

	std::cout << "ScavTrap " << this->name << " called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	this->hitPoints = 100;
	this->energyPoints = 50;
	this->attackDamage = 20;
	this->gateKeeperMode = false;

	std::cout << "ScavTrap " << this->name << " called" << std::endl;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap " << this->name << " dead" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

ScavTrap::ScavTrap(const ScavTrap& scavTrap) {
	*this = scavTrap;
}

void ScavTrap::attack(const std::string& target) {
	if (this->energyPoints > 0 && hitPoints > 0) {
		std::cout << "ScavTrap " << this->name << " attacks " << target \
		<< ", causing " << this->attackDamage << " points of damage!" << std::endl;
	}
	else {
		std::cout << "ScavTrap " << this->name << " can't attack" << std::endl;
	}
}

void ScavTrap::guardGate() {
	this->gateKeeperMode = true;
	std::cout << "Gate Keeper Mode is on-line" << std::endl;
}