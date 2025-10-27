/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:08:41 by ssohn             #+#    #+#             */
/*   Updated: 2024/04/30 13:39:10 by ssohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <fcntl.h>

char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *s, int start, int len);
char	*get_next_line(int fd);
char	*buffer_check(char **s_val, char **buffer, int fd);
char	*error_end_file(int r_count, char *res, char **buffer);
char	*ft_strchr(char *s, int c);
int		ft_strlen(char *s);

#endif
