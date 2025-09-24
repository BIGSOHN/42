CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
RM := rm -f
NAME := FragTrap
SRCS := ClapTrap.cpp \
		ScavTrap.cpp \
		FragTrap.cpp \
		main.cpp
OBJS := $(SRCS:.cpp=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "NOW_LOADING..."
	@$(CXX) $(CXXFLAGS) $? -o $@
	@echo "READY TO EVALUATE"

%.o : %.cpp
	@$(CXX) $(CXXFLAGS) -c $<

clean :
	@echo "NOW_EXECUTE_CLEANING"
	@$(RM) $(OBJS)
	@echo "THE PROCESS END"

fclean :
	@echo "NOW_EXECUTE_FCLEANING"
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@echo "THE PROCESS END"

re :
	@make fclean --no-print-directory
	@make all --no-print-directory
