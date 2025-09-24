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
		this->gateKeeperMode = other.gateKeeperMode;
	}
	return *this;
}

ScavTrap::ScavTrap(const ScavTrap& scavTrap) : ClapTrap(scavTrap) {
	this->gateKeeperMode = scavTrap.gateKeeperMode;
}

void ScavTrap::attack(const std::string& target) {
	if (this->energyPoints > 0 && hitPoints > 0) {
		std::cout << "ScavTrap " << this->name << " attacks " << target \
		<< ", causing " << this->attackDamage << " points of damage!" << std::endl;
		this->energyPoints--;
	}
	else {
		std::cout << "ScavTrap " << this->name << " can't attack" << std::endl;
	}
}

void ScavTrap::guardGate() {
	if (this->hitPoints > 0) {
		this->gateKeeperMode = true;
		std::cout << "Gate Keeper Mode is on-line" << std::endl;
	}
	else {
		std::cout << "Gate Keeper Mode failed" << std::endl;
	}
}