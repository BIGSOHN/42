#include "headers.hpp"

class Harl {
	private:
		std::string level;
		void	debug(void);
		void	info(void);
		void	warning(void);
		void	error(void);
		typedef void (Harl::*funcPtr)(void);
		funcPtr funcArray[4];
		std::string levels[4];
	public:
		Harl();
		~Harl();
		void	complain(std::string level);
};


