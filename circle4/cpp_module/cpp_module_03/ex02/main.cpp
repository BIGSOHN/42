#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main () {
	ClapTrap a;
	ScavTrap b("Bravo");
	FragTrap c = FragTrap("Charlie");
	a = ClapTrap("Alpha");
	std::cout << std::endl;

	a.attack("Charlie");
	b.attack("Delta");
	std::cout << std::endl;

	a.takeDamage(8);
	a.beRepaired(3);
	std::cout << std::endl;

	b.takeDamage(11);
	b.beRepaired(3);
	b.guardGate();
	std::cout << std::endl;

	c.takeDamage(9);
	c.beRepaired(10);
	c.attack("Alpha");
	c.highFivesGuys();
	std::cout << std::endl;
}