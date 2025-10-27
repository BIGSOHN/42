/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woonhan <woonhan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:31:18 by ssohn             #+#    #+#             */
/*   Updated: 2025/01/01 15:38:12 by woonhan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _XOPEN_SOURCE 700
# define _GNU_SOURCE
# define WRITE 0
# define UNLINK 1

# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>
# include <termios.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

extern volatile sig_atomic_t	g_flag;

typedef enum e_token_type
{
	WORD = 1,
	LITERAL,
	LOGICAL_AND,
	LOGICAL_OR,
	PIPE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	INPUT_REDIRECTION,
	OUTPUT_REDIRECTION,
	HERE_DOCUMENT,
	APPEND_REDIRECTION,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	ENVP_KEY,
	LOGIC_PIPE,
	QUOTE,
	REDIRECTION,
	PARENTHESIS,
	WHITE_SPACE,
	BACKGROUND
}	t_tok_type;

typedef enum e_error_type {
	ERR_NONE,
	ERR_CONSECUTIVE_DOTS,
	ERR_INVALID_CHAR,
	ERR_INVALID_START,
	ERR_INVALID_EXTENSION,
	ERR_INVALID_NAME,
	ERR_CONSECUTIVE_OPERATOR,
	ERR_INVALID_HIDDEN_FILE,
	ERR_INVALID_REGULAR_FILE,
	ERR_INVALID_SEQUENCE,
	ERR_INVALID_DOLLAR,
	ERR_INVALID_WORD,
}	t_error_type;

typedef struct s_syntax_error {
	char			*token;
	t_error_type	type;
}	t_syntax_error;

typedef struct s_env_node
{
	char				*envp_key;
	char				*envp_value;
	int					flag;
	struct s_env_node	*prev;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	int					size;
	struct s_env_node	*head;
	struct s_env_node	*tail;
	char				**envp_copy;
}	t_env_list;

typedef struct s_token
{
	char			*str;
	int				token_type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_tok_list
{
	int				size;
	struct s_token	*head;
	struct s_token	*tail;
}	t_tok_list;

typedef struct s_dbl_token
{
	char				**strs;
	t_tok_type			token_type;
	int					word_count;
	struct s_redir		*redir;
	struct s_dbl_token	*prev;
	struct s_dbl_token	*next;
}	t_dbl_token;

// fd -> used in here_doc
typedef struct s_redir
{
	char			*redir_sign;
	char			*file_name;
	char			*origin_file_name;
	int				fd;
	char			*limiter;
	struct s_redir	*next;
}	t_redir;

typedef struct s_dbl_list
{
	struct s_dbl_token	*head;
	struct s_dbl_token	*tail;
	int					size;
}	t_dbl_list;

typedef struct s_bt_node
{
	char				**cmd;
	int					word_count;
	struct s_redir		*redir;
	t_tok_type			type;
	struct s_bt_node	*left;
	struct s_bt_node	*right;
	int					depth;
	bool				here_doc;	
}	t_bt_node;

typedef struct s_ast_info
{
	t_dbl_token	**tok;
	t_bt_node	**cur;
	t_bt_node	**root;
}	t_ast_info;

typedef struct s_tmp
{
	size_t			idx;
	int				fd;
	struct s_tmp	*next;
}	t_tmp;

typedef struct s_tmp_list
{
	size_t			pos;
	struct s_tmp	*head;
	struct s_tmp	*tail;
}	t_tmp_list;

typedef struct s_pipe_group
{
	int	pipes[2];
	int	cmd_count;
	int	cur_cmd;
	int	pipe_count;
	int	pipe_idx;
	int	exit_status;
}	t_pipe_group;

typedef struct s_cmd_check
{
	int	sq;
	int	dq;
	int	fp;
	int	bp;
}	t_cmd_check;

typedef struct s_cmd
{
	char	**cmd;
	char	*file_name;
	size_t	idx;
}	t_cmd;

typedef struct s_pids
{
	pid_t	*pids;
	size_t	idx;
}	t_pids;

typedef struct s_backup_fd
{
	int	stdin;
	int	stdout;
	int	stderr;
}	t_backup_fd;

typedef struct s_pid_table
{
	pid_t	*pids;
	int		idx;
	size_t	pid_cnt;
}	t_pid_table;

typedef struct s_shell_context
{
	t_ast_info		*ast_info;
	t_dbl_list		*tok_list;
	t_env_list		*env_list;
	t_pipe_group	**pipe_groups;
	t_cmd			*buf;
	t_syntax_error	*syntax_error;
	t_backup_fd		backup_fd;
	t_pid_table		pid_table;
	struct termios	term;
	char			*parent_bulitin_funcs[5];
	char			*child_bulitin_funcs[4];
	void			(*parent_bulitin_func[5])(\
					t_bt_node *node, struct s_shell_context *sh_ctx);
	void			(*child_bulitin_func[4])(\
					t_bt_node *node, struct s_shell_context *sh_ctx);
	int				cur_group;
	int				max_group;
	int				max_cmd;
	int				in_fd;
	int				out_fd;
	bool			is_stdin;
	bool			is_stdout;
	char			*home_path;
	bool			is_fork;
	char			*origin_cmd;
	t_redir			*origin_dir;
}	t_sh_ctx;

//bonus_utils.c
int			preprocess_logical_operator(t_bt_node *node, t_sh_ctx *ctx);
int			exec_subshell(t_bt_node *node, t_sh_ctx *sh_ctx);

//built_in_func_cd.c
void		ft_cd(t_bt_node *node, t_sh_ctx *sh_ctx);
void		move_home(t_env_list *env_list, int *status);
void		move_dir(char *dir, t_env_list *env_list, int *status);
void		move_oldpwd(t_env_list *env_list, int *status);
void		update_pwd_envp(t_env_list *env_list, int *status);

//built_in_func_echo.c
void		ft_echo(t_bt_node *node, t_sh_ctx *sh_ctx);

//built_in_func_env.c
void		ft_env(t_bt_node *node, t_sh_ctx *sh_ctx);

//built_in_func_exit_utils.c
size_t		ft_zero_strlen(const char *s);
long long	ft_atoll(const char *nptr);
int			ft_check_valid_number(char *nptr);

//built_in_func_exit_utils2.c
char		*ft_lltoa(long long n);

//built_in_func_exit.c
void		ft_exit(t_bt_node *node, t_sh_ctx *sh_ctx);
int			is_numeric_exit_code(char *code);
void		handle_multiple_exit_args( \
			t_bt_node *node, int is_num, t_sh_ctx *ctx);
void		handle_two_exit_args( \
			t_bt_node *node, int is_numeric_arg, t_sh_ctx *ctx);
void		handle_bare_exit(t_sh_ctx *ctx);

//built_in_func_export.c
void		ft_export(t_bt_node *node, t_sh_ctx *sh_ctx);
void		export_print(t_sh_ctx *sh_ctx, int *status);
int			*make_sorting_arr(t_env_list *env_list);

//built_in_func_export2.c
void		export_env_vars(t_bt_node *node, t_sh_ctx *sh_ctx, int *status);
int			parse_export_env_command(char *cmd, t_env_list *env_list);
void		update_env_var(char *key, char *value, t_env_list *env_list);
void		extend_env_var(char *key, char *value, t_env_list *env_list);
int			is_valid_env_name(char *key);

//built_in_func_pwd.c
void		ft_pwd(t_bt_node *node, t_sh_ctx *sh_ctx);

//built_in_func_unset.c
void		ft_unset(t_bt_node *node, t_sh_ctx *sh_ctx);

// dbl_tokenlist_utils.c
t_dbl_list	*init_dbl_tokenlist(void);
void		push_dbl_token( \
			t_dbl_list *dbl_list, char **strs, int tk_type, int wc);
void		dbl_insert_fst( \
			t_dbl_list *dbl_list, char **strs, int tk_type, int wc);
void		dbl_insert_back( \
			t_dbl_list *dbl_list, char **strs, int tk_type, int wc);

// dbl_tokenlist_utils2.c
void		make_dbl_list(t_tok_list *tok_list, t_dbl_list *dbl_list);
char		**make_continuous_token_strs(t_token *ptk, int wc);
void		push_redirection(t_dbl_list *dbl_list, char *sign, char *file);
void		insert_redir_fst(t_dbl_list *dbl_list, char *sign, char *file);
void		insert_redir_last(t_dbl_list *dbl_list, char *sign, char *file);

// dbl_tokenlist_utils3.c
void		print_dbllist(t_dbl_list *dbl_list);
void		print_redir(t_redir *ptmp);
void		release_dbllist(t_dbl_list *dbl_list);
void		release_redir(t_redir *ptmp);
int			count_token(t_token *ptmp);

// dbl_tokenlist_utils4.c
int			count_before_delim(t_token *ptk);
int			count_redir_before_delim(t_token *ptk);
int			count_continuous_token(t_token *ptk);
int			count_covered_parenthesis_token(t_token *ptk);
int			count_null_before_delim(t_token *ptk);

// delimiter_utils.c
int			envp_key_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);
int			single_quote_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);
int			double_quote_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);
int			single_quoteline_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);
int			doulbe_quoteline_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);

// delimiter_utils2.c
int			redirection_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);
int			logic_pipe_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);
int			parenthesis_token( \
			t_tok_list *tok_list, char first_delim);
int			white_space_token(t_tok_list *tok_list, char first_delim);
int			next_heredoc_token( \
			t_tok_list *tok_list, char *rdline);

// delimiter_utils3.c
int			quoteline_token( \
			t_tok_list *tok_list, char first_delim, char *rdline);

//	ebnf.c
void		print_operator_error(char *token_str, t_error_type type);
void		print_syntax_error(t_sh_ctx *ctx);
int			is_redirection(char *str);
int			is_pipe(char *str);
int			is_operator(char *str);

// envplist_utils.c
t_env_list	*init_envplist(void);
void		init_envp_shlvl(t_env_list *env_list);

// envplist_utils2.c
t_env_list	*make_envp_list(char **envp);
void		make_envp_node(t_env_list *envp_list, char **envp);
void		push_envp_node(t_env_list *envp_list, char *e_key, char *e_value);
void		env_insert_at_first( \
			t_env_list *envp_list, char *e_key, char *e_val);
void		env_insert_at_back( \
			t_env_list *envp_list, char *ekey, char *e_val);

// envplist_utils3.c
char		*exrtact_env_key(char *str);
char		*extract_env_value(char *str);
char		*extract_env_sign(char *str);
char		**envp_join(t_env_list *envp_list);
int			count_active_env_nodes(t_env_list *envp_list);

// envplist_utils4.c
t_env_node	*find_envp_node(t_env_list *envp_list, char *key);
char		*find_envp_value(t_env_list *envp_list, char *e_key);
void		print_envplist(t_env_list *envp_list);
void		release_envplist(t_env_list *envp_list);
void		release_envpcopy(t_env_list *envp_list);

//	error_func.c
void		terminate_on_error(char *s);

//	error_handler.c
void		do_sigint_heredoc(int signum);
void		here_doc_quit_signal_handler(int signo);
void		child_quit_signal_handler(int signo);
void		child_int_signal_handler(int signo);
void		sig_quit_handler(int signo);

//	execute_command.c
void		exception_handler(const char *str, t_sh_ctx *ctx);
void		run_command(t_sh_ctx *ctx, t_bt_node *node, int mode);
void		check_and_execute(t_bt_node *cur_node, t_sh_ctx *sh_ctx);

// execute_command2.c
int			check_relative_path(char **s, t_sh_ctx *ctx);
char		*get_error_message(t_sh_ctx *ctx, int *status);
void		postprocess_builtin(t_sh_ctx *ctx);
void		print_error_and_set_status(const char *message, const char *path, \
			const char *status_code);
void		handle_error_type(const char *path);

// execute_command3.c
void		handle_chdir_error(const char *path, char **s, t_sh_ctx *ctx);
int			change_dir(char *cmd, char *path, char **s, t_sh_ctx *ctx);

//	exit_utils.c
int			is_special_command(char **s, char *chunk, t_sh_ctx *ctx, int *i);
int			my_exit(long long code);
int			contains_digit(char	*s);
long long	truncate_8bits(char *str);

//	file_redirection_funcs_utils.c
void		print_input_error_msg(t_redir *redir, t_sh_ctx *ctx, char *tmp);
void		handle_exception_input_redir( \
			t_redir *redir, t_sh_ctx *ctx, char *tmp);
void		print_output_error_msg(t_redir *redir, t_sh_ctx *ctx, char *tmp);
void		handle_exception_output_redir( \
			t_redir *redir, t_sh_ctx *ctx, char *tmp);

//	file_redirection_funcs.c
void		exec_heredoc_redir(t_redir *redir, t_sh_ctx *sh_ctx);
void		exec_input_redir(t_redir *redir, t_sh_ctx *sh_ctx);
void		exec_output_redir(t_redir *redir, t_sh_ctx *sh_ctx);
void		exec_append_redir(t_redir *redir, t_sh_ctx *sh_ctx);

// find_tokentype_utils.c
int			notice_token_type(char *str, int token_type);
int			redir_token_type(char *str);
int			lp_token_type(char *str);
int			parenthesis_token_type(char *str);
int			find_prev_token_type(t_token *ptoken);

// find_tokentype_utils2.c
int			is_redirection_token(t_token *ptk);

//	generator_chunk_utils.c
void		separate_into_chunks(char **chunk, t_sh_ctx *ctx, size_t *idx);
char		*initialize(size_t *idx, t_sh_ctx *ctx, char **init, char *s);
void		handle_special_char( \
			char **s, char *chunk, size_t *idx, t_sh_ctx *ctx);
void		substitute_cmd_variable(char *s, t_sh_ctx *ctx);
void		strings_to_chunk(t_bt_node *node, t_sh_ctx *ctx);

//	generator_chunk_utils2.c
int			resize_cmd_buffer(t_sh_ctx *ctx);
int			copy_env_value(char *chunk, char *val, t_sh_ctx *ctx);
void		substitute_file_name(char *s, t_sh_ctx *ctx);

// generator_chunk_utils3.c
int			get_value_len(char *val);
int			handle_env_variable_len(char **s, t_sh_ctx *ctx);
size_t		env_to_len(char **s, t_sh_ctx *ctx);
size_t		single_quote_strlen(char **s);
size_t		double_quote_strlen(char **s, t_sh_ctx *ctx);

// generator_chunk_util4.c
int			handle_exception_len(char **s, t_sh_ctx *ctx, int *i);
int			special_command_len(char **s, t_sh_ctx *ctx, int *i);
void		handle_special_char_length(char **s, size_t *len, t_sh_ctx *ctx);
int			check_string_length(char *s, t_sh_ctx *ctx);

//	generator_redirection.c
void		file_redirection(t_bt_node *node, t_sh_ctx *ctx);
void		stdin_redirection(int *in, t_sh_ctx *ctx);
void		file_stdout_redirection(int *out, t_sh_ctx *ctx);
void		stdout_redirection(int *out, t_sh_ctx *ctx);
void		pipe_redirection(t_bt_node *cur_node, t_sh_ctx *ctx);

//	generator_redirection2.c
void		close_pipe_redirection(t_sh_ctx *ctx);

//	generator_string_utils.c
int			env_to_text(char **s, char *chunk, t_sh_ctx *ctx);
int			process_single_quote(char **s, char *chunk);
int			process_double_quote(char **s, char *chunk, t_sh_ctx *ctx);
int			handle_env_variable(char **s, char *chunk, t_sh_ctx *ctx);

//	generator_utils.c
int			execute_builtin_chlid(t_bt_node *node, t_sh_ctx *sh_ctx);
int			execute_builtin_parent(t_bt_node *node, t_sh_ctx *sh_ctx);
int			initialize_exec(t_sh_ctx *ctx);
int			postprocess(t_sh_ctx *ctx);

//	generator.c
int			exec_command(t_sh_ctx *ctx);
void		parent_pipe_redirection(t_sh_ctx *ctx);
void		exec_other_command(t_bt_node *node, t_sh_ctx *ctx);
int			exec_chlid_process(t_bt_node *node, t_sh_ctx *ctx);
int			exec_in_order(t_bt_node *node, t_sh_ctx *sh_ctx);

//	generator2.c
void		handle_fork_exception(t_sh_ctx *ctx);
void		restore_fd(t_sh_ctx *ctx);
void		set_chlid_signal_attr(void);

//	lexer.c
int			is_restricted_token_type(t_tok_type type);
int			check_restricted_tokens(t_token *tok, t_sh_ctx *ctx);
int			lexer(t_token *tok, t_sh_ctx *ctx);

// lexer_utils.c
int			command(t_token *tok, t_sh_ctx *ctx);
int			process_command_elements( \
			t_token *current, t_sh_ctx *ctx, t_syntax_error *temp);
int			check_initial_command(t_token *tok, t_syntax_error *temp);
int			check_token_sequence(t_token *tok, t_syntax_error *temp);
int			check_consecutive_operators(t_token *current, t_syntax_error *temp);

// lexer_utils2.c
int			command(t_token *tok, t_sh_ctx *ctx);
void		set_temp_error( \
			t_syntax_error *temp, char *token, t_error_type type);
void		apply_error(t_sh_ctx *ctx, t_syntax_error *temp);
void		init_temp_error(t_syntax_error *temp);

// main.c
int			set_home_path(t_sh_ctx *ctx, char **envp);
void		init_shell_context(t_sh_ctx **sh_ctx, char **envp);
int			process_cmd(char *line, t_sh_ctx *ctx);

// make_token_utils.c
int			tokenize(char *rdline, t_sh_ctx *sh_ctx);
void		make_token(t_tok_list *token_list, char *rdline);
int			check_delim(char rd_char);

// other_func.c
int			*get_exit_status(void);
char		*ft_realloc(char *chunk, int *size);
char		*get_path_variable(char **envp);
int			*get_sig_quit_flag(void);

// parser_utils.c
int			check_here_doc(t_redir *redir, t_sh_ctx *ctx, int flag);
int			make_tmp_file(t_redir *redir, t_sh_ctx *ctx);
void		preprocess_heredoc(t_redir *redir, t_sh_ctx *ctx);
int			postprocess_heredoc(int fd, t_sh_ctx *ctx);

// parser_utils2.c
int			process_double_quote_for_here_doc(char **s, char *chunk);
char		*preprocess_limiter(char *s);
int			handle_here_doc_exception(t_redir *redir, int fd, t_sh_ctx *ctx);

// parser_utils3.c
char		*get_env_value(char *s, size_t *idx, t_sh_ctx *ctx);
char		*env_to_text_in_heredoc(char *s, t_sh_ctx *ctx);
int			write_heredoc(t_redir *redir, t_sh_ctx *ctx);

// parser.c
t_bt_node	*create_node(t_dbl_token **tok, t_bt_node **node);
void		parse_subshell(t_ast_info *ast_info);
char		**dup_2d_array(char **src);
t_bt_node	*copy_node(t_bt_node *orignal);
void		reallocate_pipegroups(t_sh_ctx *sh_ctx);
void		add_pipe_group(t_sh_ctx *ctx);
void		set_root( \
			t_ast_info *ast_info, t_bt_node **orig_cur, t_sh_ctx *sh_ctx);
int			set_binary_tree(t_ast_info *ast_info, t_sh_ctx *ctx);
void		set_pipe_groups(t_sh_ctx *ctx);
int			parse_command(t_sh_ctx *ctx);

//	preprocessor.c
int			preprocess(char *line, t_sh_ctx **sh_ctx, char **envp);

// push_token_utils.c
void		push_token_to_list(t_tok_list *tok_list, char *str, int token_type);
int			fill_delim_token(t_tok_list *tok_list, char *rdline, char *rd_str);
void		push_token(t_tok_list *tok_list, char *str, int token_flag);
void		fill_literal_token(t_tok_list *tok_list, char *str, int token_type);

//	redirection_list.c
int			is_consecutive_redirection(char *curr, char *next);
int			check_redirection_sequence(t_token *tok, t_syntax_error *temp);
int			check_redirection_validity(t_token *tok, t_syntax_error *temp);
int			check_redirection_end(t_token *curr, t_syntax_error *temp);
int			check_redirection_syntax(t_token *curr, t_sh_ctx *ctx);
int			redirection(t_token *tok, t_sh_ctx *ctx);
int			redirection_list(t_token *tok, t_sh_ctx *ctx);

// replace_token_utils.c
int			check_delim_envp_symbol(char rd_char);
void		replace_envp_token(t_tok_list *token_list, t_env_list *envp_list);
void		change_envp_str(t_token *p_token, t_env_list *envp_list);
void		change_envp_key_to_value(t_token *p_token, char *e_value);

// replace_token_utils2.c
void		join_continuous_token(t_tok_list *token_list);
t_token		*find_continuous_token(t_tok_list *token_list, int token_type);
void		join_same_token(t_tok_list *token_list, int token_type);

// replace_token_utils3.c
void		change_token_type_to_literal(t_tok_list *token_list);

// shell_command.c
int			check_command(t_token *tok, t_sh_ctx *ctx, t_syntax_error *temp);
int			handle_pipe_error( \
			t_token *tok, t_sh_ctx *ctx, t_syntax_error *temp, int error_type);
int			check_pipeline_validity(t_token *tok, t_syntax_error *temp);
int			check_pipeline_sequence( \
			t_token *tok, t_syntax_error *temp, t_sh_ctx *ctx);

// shell_command2.c

int			pipeline(t_token *tok, t_sh_ctx *ctx);
int			check_initial_pipe_sequence(t_token *tok, t_syntax_error *temp);
int			check_consecutive_pipes(t_token *tok, t_syntax_error *temp);
int			check_compound_sequence( \
			t_token *tok, t_syntax_error *temp, t_sh_ctx *ctx);

// shell_command3.c
int			handle_error( \
			t_token *tok, t_sh_ctx *ctx, t_syntax_error *temp, int print_err);
int			is_logical_operator(t_token *tok);
int			compound_list(t_token *tok, t_sh_ctx *ctx);
int			pipeline_command(t_token *tok, t_sh_ctx *ctx);
int			compound_command(t_token *tok, t_sh_ctx *ctx);

// shell_command4.c

int			check_subshell_closing(t_token *tok, t_syntax_error *temp);
int			subshell(t_token *tok, t_sh_ctx *ctx);
int			shell_command(t_token *tok, t_sh_ctx *ctx);
int			check_next_command( \
			t_token **current, t_sh_ctx *ctx, t_syntax_error *temp);

//	shell_func_utils.c
void		init_shell_cmd(t_sh_ctx *sh_ctx);
void		init_shell_funcs(t_sh_ctx *sh_ctx);

//	signal.c
void		process_sigterm(void);
void		process_sigint(int signum);
void		signal_handler(int signal_number, siginfo_t *info, void *context);
void		init_term_attr(void);
void		init_signal_attr(t_sh_ctx *ctx);

void		null_handle_exception(t_redir *redir, int fd, t_sh_ctx *ctx);
void		sigint_handle_exception(t_redir *redir, int fd, t_sh_ctx *ctx);

//	simple_command.c
int			letter(char c);
int			special_char(char c);
int			check_regular_extension( \
			char **s, t_syntax_error *temp, t_sh_ctx *ctx);
int			check_hidden_extension( \
			char **s, t_syntax_error *temp, t_sh_ctx *ctx);
int			process_hidden_name(char **s, t_syntax_error *temp, t_sh_ctx *ctx);
int			filename(t_token *tok, t_sh_ctx *ctx);
int			regularfile(t_token *tok, t_sh_ctx *ctx);
int			hiddenfile(t_token *tok, t_sh_ctx *ctx);
int			check_namepart_chars( \
			char *str, t_syntax_error *temp, t_sh_ctx *ctx);
int			namepart(char **str, t_sh_ctx *ctx);
int			check_no_dot_chars(char **s, t_syntax_error *temp, t_sh_ctx *ctx);
int			namepart_no_dot(char **s, t_sh_ctx *ctx);
int			filechar(char c, t_sh_ctx *ctx);
int			filechar_no_dot(char c, t_sh_ctx *ctx);
int			dollar(t_token *tok, t_sh_ctx *ctx);
int			regular_word(t_token *tok, t_sh_ctx *ctx);
int			word(t_token *tok, t_sh_ctx *ctx);
int			check_name_chars(char *str, t_syntax_error *temp);
int			check_quoted_content( \
			char *str, char quote_char, t_syntax_error *temp);
int			single_quoted_content(t_token *tok, t_sh_ctx *ctx);
int			single_quoted_string(t_token *tok, t_sh_ctx *ctx);
int			double_quoted_content(t_token *tok, t_sh_ctx *ctx);
int			double_quoted_string(t_token *tok, t_sh_ctx *ctx);
int			literal(t_token *tok, t_sh_ctx *ctx);
int			check_assignment_sequence(t_token *tok, t_sh_ctx *ctx);
int			check_value_token(t_token *value_token, t_sh_ctx *ctx);
int			check_assignment_syntax(t_token *tok, t_sh_ctx *ctx);
int			assignment_word(t_token *tok, t_sh_ctx *ctx);
int			simple_command_element(t_token *tok, t_sh_ctx *ctx);
int			simple_command(t_token *tok, t_sh_ctx *ctx);

// simple_command2.c
int			is_valid_path_char(char c);

// simple_command3.c
int			validate_path(const char *path);

// simple_command8.c
int			check_pipe_syntax(t_token *tok);

// simple_command10.c
int			is_home_path(const char *path);
char		*get_path_after_home(const char *path);
int			special_path(t_token *tok, t_sh_ctx *ctx);
int			simple_command(t_token *tok, t_sh_ctx *ctx);
int			process_command_tokens( \
			t_token *current, t_sh_ctx *ctx, t_syntax_error *temp);

// syntax_check.c
int			check_syntax(char *readline);
int			check_quote(char *readline);
int			check_parenthesis(char *readline);
int			len_except_qline(char *readline);
char		*make_except_quoteline(char *rdline, char *nqline);

//	terminal.c
void		set_terminal_print_off(void);
void		set_parent_term_attr(void);
void		set_child_term_attr(t_bt_node *node);
void		set_here_doc_terminal_attr(t_sh_ctx *ctx);
void		init_term_attr(void);

// tokenlist_utils.c
t_tok_list	*init_tokenlist(void);
void		tok_insert_at_first( \
			t_tok_list	*tok_list, char *str, int token_type);
void		tok_insert_at_back( \
			t_tok_list *tok_list, char *str, int token_type);
void		release_tokenlist(t_tok_list *tok_list);
void		print_tokenlist(t_tok_list *tok_list);

// tokenlist_utils2.c
void		delete_token_node(t_tok_list *tok_list, int token_type);
void		delete_specific_node(t_tok_list *tok_list, t_token *delete_node);
void		replace_token_pointer(t_tok_list *tok_list, t_token *ptoken);
t_token		*find_token_node(t_tok_list *tok_list, int token_type);

#endif