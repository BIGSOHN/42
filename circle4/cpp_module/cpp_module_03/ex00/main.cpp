#include "ClapTrap.hpp"

int main () {
	ClapTrap a;
	ClapTrap b("Bravo");
	ClapTrap c = ClapTrap("Charlie");
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
	std::cout << std::endl;

	c.takeDamage(9);
	for (int i = 0; i < 10; i++) {
		c.beRepaired(1);
	}
	c.attack("Alpha");
	std::cout << std::endl;
}