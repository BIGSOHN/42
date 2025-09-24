# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 13:41:03 by ssohn             #+#    #+#              #
#    Updated: 2024/07/18 17:43:59 by ssohn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAG := -Wall -Wextra -Werror
RM := rm -f
NAME := pipex
SRCS := error_utils.c \
		full_range_utils.c \
		main.c \
		path_utils.c \
		pipe_utils.c \
		process_in_function.c \
		process_utils.c \
		single_quote_split_utils.c \
		

OBJS := $(SRCS:.c=.o)
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "NOW_LOADING..."
	@make -C $(LIBFT_DIR) all --no-print-directory
	@$(CC) $(CFLAG) $? $(LIBFT) -o $@
	@echo "READY TO EVALUATE"

%.o : %.c
	@$(CC) $(CFLAGS) -c $? -g

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
