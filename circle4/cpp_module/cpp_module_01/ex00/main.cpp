#include "headers.hpp"
#include "Zombie.hpp"

int main (void) {
	Zombie zombie1("Zombie1");
	zombie1.announce();
	Zombie *zombie2 = newZombie("Zombie2");
	zombie2->announce();
	delete(zombie2);
	randomChump("Zombie3");
}