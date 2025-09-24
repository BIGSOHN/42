CC := cc
CFLAG := -Wall -Wextra -Werror
RM := rm -f
NAME := push_swap
SRCS := main.c \
		input.c \
		is_error.c \
		is_error_2.c \
		push_util.c \
		stack_utils.c \
		ft_lst_init_input.c \
		ft_lst_del.c \
		ft_swap.c \
		ft_push_stack.c \
		ft_rotate.c \
		three_sort.c \
		index_sort.c \
		two_sort.c \
		sort_count_node.c \
		sort_greedy_utils.c \
		sort_greedy.c

OBJS := $(SRCS:.c=.o)
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C $(LIBFT_DIR) all --no-print-directory
	@echo "libft.a"
	@$(CC) $(CFLAG) $? $(LIBFT) -o $@

%.o : %.c
	@$(CC) $(CFLAGS) -c $?

clean :
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@$(RM) $(OBJS)

fclean :
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) $(OBJS)
	@$(RM) $(NAME)

re :
	@make fclean --no-print-directory
	@make all --no-print-directory
