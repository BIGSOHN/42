#ifndef FragTRAP_HPP
# define FragTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
private:

public:
	FragTrap();
	FragTrap(std::string name);
	~FragTrap();
	FragTrap& operator=(const FragTrap& other);
	FragTrap(const FragTrap& fragTrap);
	
	void attack(const std::string& target);
	void highFivesGuys(void);
};

#endif