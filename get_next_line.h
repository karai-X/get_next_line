/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:08:38 by karai             #+#    #+#             */
/*   Updated: 2024/11/03 23:15:34 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	size_t			length;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
char				*ft_strdupgnl_lstfree(const char *s, size_t src_len,
						t_list *lst_first, size_t i);
bool				ft_lst_append(size_t read_byte, char *input_str,
						t_list *lst_first);
size_t				ft_lst_combine_part(t_list *ptr);
char				*ft_lst_combine(t_list *lst_first);
bool				ft_get_next_buf(char buf[BUFFER_SIZE], t_list *lst_first,
						bool *end_flag, ssize_t *read_byte);

#endif
