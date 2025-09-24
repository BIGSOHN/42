#include "headers.hpp"
#include "Zombie.hpp"

int main (void) {
	int n = 5;
	std::string name = "zombie";

	Zombie *zoms = zombieHorde(n, name);
	for (int i = 0; i < n; i++) {
		zoms[i].announce();
	}
	delete[] zoms;
}