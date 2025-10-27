CC := cc
CFLAG := -Wall -Wextra -Werror
AR := ar rc
RM := rm -f
NAME := libftprintf.a
SRCS :=	ft_printf.c \
		ft_printf_chars.c \
		ft_printf_number.c \
		ft_printf_pointer.c \
		ft_printf_simple_util.c

OBJS := $(SRCS:.c=.o)
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	make -C $(LIBFT_DIR) all
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $?

%.o : %.c
	$(CC) $(CFLAGS) -c $?

clean :
	make -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean :
	make -C $(LIBFT_DIR) fclean
	$(RM) $(OBJS)
	$(RM) $(NAME)

re :
	make fclean
	make all
