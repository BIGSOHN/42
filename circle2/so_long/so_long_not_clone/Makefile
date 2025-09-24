# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 13:41:03 by ssohn             #+#    #+#              #
#    Updated: 2024/08/09 16:42:16 by ssohn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAG := -Wall -Wextra -Werror -g
RM := rm -f
NAME := so_long
SRCS := main.c \
		map_utils.c \
		error_msg.c	\
		full_range_utils.c \
		map_valid_utils.c \
		map_valid_wall_utils.c \
		map_valid_element_utils.c \
		game.c \
		draw.c \
		event.c \
		key_event.c \
		path_struct_utils.c \
		map_valid_path.c \
		

OBJS := $(SRCS:.c=.o)
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a
MINILIBX_DIR := ./minilibx-linux

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "NOW_LOADING..."
	@make -C $(LIBFT_DIR) all --no-print-directory
	@make -C $(MINILIBX_DIR) all --no-print-directory
	@$(CC) $(CFLAG) $? $(LIBFT) -L./minilibx-linux -lmlx_Linux -L/usr/lib -I./minilibx-linux -lXext -lX11 -lm -lz -o $@
	@echo "READY TO EVALUATE"

%.o : %.c
	@$(CC) $(CFLAGS) -c $?

clean :
	@echo "NOW_EXECUTE_CLEANING"
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@make -C $(MINILIBX_DIR) clean --no-print-directory
	@$(RM) $(OBJS)
	@echo "THE PROCESS END"

fclean :
	@echo "NOW_EXECUTE_FCLEANING"
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(MINILIBX_DIR) clean --no-print-directory
	@$(RM) $(OBJS)
	@$(RM) $(NAME)
	@echo "THE PROCESS END"

re :
	@make fclean --no-print-directory
	@make all --no-print-directory
