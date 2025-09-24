#ifndef HUMANB_HPP
# define HUMANB_HPP

#include "headers.hpp"
#include "classes.hpp"

class HumanB {
	private:
		std::string	name;
		Weapon	*weapon;
	public:
		HumanB();
		HumanB(std::string name);
		~HumanB();
		void	attack();
		void	setWeapon(Weapon& weapon);
};

#endif