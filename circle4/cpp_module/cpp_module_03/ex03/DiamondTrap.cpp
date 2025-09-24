#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
: ClapTrap("Default_clap_name"), ScavTrap("Default"), FragTrap("Default"), name("Default") {
	this->energyPoints = 50;

	std::cout << "DiamondTrap " << this->name << " called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name)
: ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name), name(name) {
	this->energyPoints = 50;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap " << this->name << " dead" << std::endl;
}
DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	return *this;
}

DiamondTrap::DiamondTrap(const DiamondTrap& diamondTrap)
 : ClapTrap(diamondTrap), ScavTrap(diamondTrap), FragTrap(diamondTrap), name(diamondTrap.name) {

}

void DiamondTrap::attack(const std::string& target) {
	ScavTrap::attack(target);
}

void DiamondTrap::whoAmI() {
	std::cout << "DiamondTrap's name is " << this->name << std::endl;
	std::cout << "ClapTrap's name is " << ClapTrap::name << std::endl;
}