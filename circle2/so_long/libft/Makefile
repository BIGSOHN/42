# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssohn <ssohn@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 11:21:13 by ssohn             #+#    #+#              #
#    Updated: 2024/08/08 11:55:39 by ssohn            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := cc
CFLAG := -Wall -Wextra -Werror -g
NAME := libft.a
SRCS := ft_atoi.c \
ft_bzero.c \
ft_calloc.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_itoa.c \
ft_memchr.c \
ft_memcmp.c \
ft_memmove.c \
ft_memset.c \
ft_memcpy.c \
ft_putchar_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr_fd.c \
ft_split.c \
ft_strchr.c \
ft_strdup.c \
ft_striteri.c \
ft_strjoin.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strmapi.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_strtrim.c \
ft_substr.c \
ft_tolower.c \
ft_toupper.c \
get_next_line.c \
ft_printf.c \
ft_printf_chars.c \
ft_printf_number.c \
ft_printf_pointer.c \
ft_printf_simple_util.c

BSRCS := ft_lstnew.c \
ft_lstadd_front.c \
ft_lstsize.c \
ft_lstlast.c \
ft_lstadd_back.c \
ft_lstdelone.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstmap.c

OBJS := $(SRCS:.c=.o)

BOBJS := $(BSRCS:.c=.o)

.PHONY : all clean fclean re bonus

all : $(NAME)

bonus : $(BOBJS)

$(NAME) : $(OBJS)

%.o : %.c
	@$(CC) $(CFLAGS) -c $<
	@ar -rcs $(NAME) $@

clean :
	@rm -f $(OBJS) $(BOBJS)

fclean : clean
	@rm -f $(NAME)

re :
	@make fclean
	@make all
