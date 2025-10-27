CC := cc
CFLAG := -Wall -Wextra -Werror -g #-fsanitize=thread
RM := rm -f
NAME := philo
SRCS := philo_behavior_eat_function.c \
		philo_behavior_function.c \
		philo_cleanup.c \
		philo_init_function.c \
		philo_monitoring.c \
		philo_utils.c \
		philo_libftutils.c	\
		philo_is_error.c \
		philo_utils.c \
		main.c \

OBJS := $(SRCS:.c=.o)

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "NOW_LOADING..."
	@$(CC) $(CFLAG) $? -o $@
	@echo "READY TO EVALUATE"

%.o : %.c
	@$(CC) $(CFLAG) -c $?

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
