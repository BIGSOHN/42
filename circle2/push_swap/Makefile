# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssohn <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 13:41:03 by ssohn             #+#    #+#              #
#    Updated: 2024/07/05 13:25:57 by ssohn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
	@echo "NOW_LOADING..."
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAG) $? $(LIBFT) -o $@
	@echo "READY TO EVALUATE"

%.o : %.c
	@$(CC) $(CFLAGS) -c $?

clean :
	@echo "NOW_EXECUTE_CLEANING"
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@$(RM) $(OBJS)
	@echo "THE PROCESS END"

fclean :
	@echo "NOW_EXECUTE_FCLEANING"
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@echo "THE PROCESS END"

re :
	@make fclean --no-print-directory
	@make all --no-print-directory
