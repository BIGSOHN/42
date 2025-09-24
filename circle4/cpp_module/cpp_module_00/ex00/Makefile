CC := c++
CFLAG := -Wall -Wextra -Werror -std=c++98 -g
RM := rm -f
NAME := megaphone
SRCS := megaphone.cpp

OBJS := $(SRCS:.cpp=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "NOW_LOADING..."
	@$(CC) $(CFLAG) $? -o $@
	@echo "READY TO EVALUATE"

%.o : %.cpp
	@$(CC) $(CFLAGS) -c $<

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
