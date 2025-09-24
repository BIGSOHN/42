/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:59:04 by ssohn             #+#    #+#             */
/*   Updated: 2024/06/21 17:55:11 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include "libft/libft.h"

typedef struct s_node
{
	int					content;
	int					index;
	struct s_node		*prev;
	struct s_node		*next;
	struct s_node_info	*info;
}t_node;
typedef struct s_node_info
{
	int	ra_count;
	int	rb_count;
	int	rra_count;
	int	rrb_count;
}t_node_info;
typedef struct s_stack
{
	int				size;
	char			stack_name;
	struct s_node	*head;
	struct s_node	*tail;
}t_stack;

int			is_error(int argc, char **argv);
int			is_input_invalid(int argc, char **argv);
int			is_int_range(int argc, char **argv);
int			is_duplicated(int *num_list, int count_number);
int			is_argv_space(int argc, char **argv);
int			count_number(int argc, char **argv);
int			*input_number(int argc, char **argv, int number_count);
int			*input_index(int *num_list, int num_count);
int			input_stack_node(int argc, char **argv, t_stack *stack);
int			is_first_sorted(int argc, char **argv);
long long	ft_atoll(const char *nptr);
int			ft_count_word(char *s, char c);
char		**double_pointer_free(char **dest, int num);
int			ft_check_valid_number(char *nptr);
t_stack		*init_stack(char name);
void		push(t_stack *stack, int num, int index);
int			insert_at_front(t_stack *stack, int num, int index);
int			insert_at_back(t_stack *stack, int num, int index);
int			insert_at_first(t_stack *stack, int num, int index);
int			delete_at_head(t_stack *stack);
int			delete_at_tail(t_stack *stack);
int			delete_at_last(t_stack *stack);
void		printlist(t_stack *stack, int num_count);
void		printbacklist(t_stack *stack, int num_count);
void		release_stack(t_stack *stack);
int			is_empty(t_stack *stack);
int			ft_swap(t_stack *stack);
int			ft_swap_ss(t_stack *stack_a, t_stack *stack_b);
int			push_stack_a(t_stack *stack_a, t_stack *stack_b);
int			push_stack_b(t_stack *stack_b, t_stack *stack_a);
void		push_stack(t_stack *stack, int num, int index);
int			rotate_stack(t_stack *stack);
int			reverse_rotate_stack(t_stack *stack);
int			three_is_sorted(t_stack *stack);
int			min_index_first(int temp_a, int temp_b, int temp_c, t_stack *stack);
int			mid_index_first(int temp_a, int temp_b, int temp_c, t_stack *stack);
int			max_index_first(int temp_a, int temp_b, int temp_c, t_stack *stack);
int			left_sorted_three_node(t_stack *stack_a, t_stack *stack_b);
int			group_small(t_stack *stack_a, t_stack *stack_b);
int			group_mid(t_stack *stack_a, t_stack *stack_b);
int			group_big(t_stack *stack_a, t_stack *stack_b, int input_num);
int			two_is_sorted(t_stack *stack);
int			count_all_inst(t_node_info *node_info);
int			count_top_stack_b(t_stack *stack_b);
int			count_stack_a_make_top(t_stack *stack_b, t_stack *stack_a);
void		write_all_count(t_stack *stack_a, t_stack *stack_b);
void		re_zero_info(t_stack *stack_b);
int			is_sorted(t_stack *stack);
t_node		*find_min_a_node(t_stack *stack_a);
int			find_min_idx_loc(t_stack *stack);
int			loc_min_idx_bigger_than_b(t_stack *stack_a, int b_index);
int			biggest_index(t_stack *stack_a);
t_node		*find_min_count_node(t_stack *stack_b);
int			exec_greedy(t_stack *stack_a, t_stack *stack_b);
int			exec_inst(t_node *pmin, t_stack *stack_a, t_stack *stack_b);
int			exec_stack_rotate(int mv_count, t_stack *stack);
int			exec_stack_reverse_rotate(int mv_count, t_stack *stack);
#endif
