CC := gcc
CFLAGS := -Wall -Wextra -Werror -g #-fsanitize=address
RM := rm -f
NAME := minishell
SRCS :=	bonus_utils.c	\
		built_in_func_cd.c	\
		built_in_func_echo.c	\
		built_in_func_env.c	\
		built_in_func_exit.c	\
		built_in_func_exit_utils.c	\
		built_in_func_exit_utils2.c \
		built_in_func_export2.c	\
		built_in_func_export.c	\
		built_in_func_pwd.c	\
		built_in_func_unset.c	\
		dbl_tokenlist_utils2.c	\
		dbl_tokenlist_utils3.c	\
		dbl_tokenlist_utils4.c	\
		dbl_tokenlist_utils.c	\
		delimiter_utils2.c	\
		delimiter_utils3.c	\
		delimiter_utils.c	\
		ebnf.c	\
		envplist_utils2.c	\
		envplist_utils3.c	\
		envplist_utils4.c	\
		envplist_utils.c	\
		error_func.c	\
		error_handler.c	\
		execute_command.c	\
		execute_command2.c	\
		execute_command3.c	\
		exit_utils.c	\
		file_redirection_funcs.c	\
		file_redirection_funcs_utils.c	\
		find_tokentype_utils2.c	\
		find_tokentype_utils.c	\
		generator2.c	\
		generator.c	\
		generator_chunk_utils4.c	\
		generator_chunk_utils3.c	\
		generator_chunk_utils2.c	\
		generator_chunk_utils.c	\
		generator_redirection2.c	\
		generator_redirection.c	\
		generator_string_utils.c	\
		generator_utils.c	\
		lexer.c	\
		lexer_utils.c 	\
		lexer_utils2.c	\
		main.c	\
		make_token_utils.c	\
		other_func.c	\
		parser.c	\
		parser2.c	\
		parser_utils.c	\
		parser_utils2.c	\
		parser_utils3.c	\
		preprocessor.c	\
		push_token_utils.c	\
		redirection_list.c	\
		redirection_list2.c	\
		replace_token_utils2.c	\
		replace_token_utils3.c	\
		replace_token_utils.c	\
		shell_command.c	\
		shell_command2.c	\
		shell_command3.c	\
		shell_command4.c	\
		shell_func_utils.c	\
		signal.c	\
		simple_command.c	\
		simple_command2.c	\
		simple_command3.c	\
		simple_command4.c	\
		simple_command5.c	\
		simple_command6.c	\
		simple_command7.c	\
		simple_command8.c	\
		simple_command9.c	\
		simple_command10.c	\
		syntax_check.c	\
		terminal.c	\
		tokenlist_utils2.c	\
		tokenlist_utils.c	\

OBJS := $(SRCS:.c=.o)
LIBFT_DIR := ./libft
LIBFT := $(LIBFT_DIR)/libft.a

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJS)
	@echo "NOW_LOADING..."
	@make -C $(LIBFT_DIR) all --no-print-directory
	@make -C $(LIBFT_DIR) bonus --no-print-directory
	@$(CC) $(CFLAGS) $? $(LIBFT) -o $@ -lreadline
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
