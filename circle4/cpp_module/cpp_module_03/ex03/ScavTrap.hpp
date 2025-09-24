#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
private:
	bool gateKeeperMode;
public:
	ScavTrap();
	ScavTrap(std::string name);
	~ScavTrap();
	ScavTrap& operator=(const ScavTrap& other);
	ScavTrap(const ScavTrap& scavTrap);
	
	void attack(const std::string& target);
	void guardGate();
};

#endif