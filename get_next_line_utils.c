/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:38:42 by karai             #+#    #+#             */
/*   Updated: 2024/11/24 15:22:44 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdupgnl_lstfree(const char *s, size_t src_len, t_list *lst_first,
		size_t i)
{
	char	*copy_src;
	t_list	*ptr;

	if (lst_first == NULL)
	{
		copy_src = (char *)malloc(sizeof(char) * src_len);
		if (copy_src == NULL)
			return (NULL);
		i = 0;
		while (i < src_len)
		{
			copy_src[i] = s[i];
			i += 1;
		}
		return (copy_src);
	}
	while (lst_first != NULL && lst_first->next != NULL)
	{
		ptr = lst_first->next->next;
		if (lst_first->next->content != NULL)
			free(lst_first->next->content);
		free(lst_first->next);
		lst_first->next = ptr;
	}
	return (NULL);
}

bool	ft_lst_append(size_t read_byte, char *input_str, t_list *lst_first)
{
	t_list	*ptr;

	if (lst_first->next == NULL)
		ptr = lst_first;
	else
	{
		ptr = lst_first->next;
		while (ptr->next != NULL)
			ptr = ptr->next;
	}
	ptr->next = (t_list *)malloc(sizeof(t_list));
	if (ptr->next == NULL)
		return (false);
	ptr->next->content = ft_strdupgnl_lstfree(input_str, read_byte, NULL, 0);
	if (ptr->next->content == NULL)
		return (false);
	ptr->next->length = read_byte;
	ptr->next->next = NULL;
	return (true);
}

size_t	ft_lst_combine_part(t_list *ptr)
{
	size_t	size;

	size = 0;
	while (ptr != NULL)
	{
		if (SIZE_MAX - size - 1 < ptr->length)
			return (0);
		size += ptr->length;
		ptr = ptr->next;
	}
	return (size);
}

char	*ft_lst_combine(t_list *lst_first)
{
	t_list	*ptr;
	size_t	size;
	char	*ret_str;
	size_t	j;

	size = ft_lst_combine_part(lst_first->next);
	if (size == 0)
		return (ft_strdupgnl_lstfree(NULL, 0, lst_first, 0));
	ret_str = (char *)malloc(sizeof(char) * (size + 1));
	if (ret_str == NULL)
		return (ft_strdupgnl_lstfree(NULL, 0, lst_first, 0));
	ptr = lst_first->next;
	j = 0;
	while (ptr != NULL)
	{
		size = 0;
		while (size < ptr->length)
			ret_str[j++] = ptr->content[size++];
		ptr = ptr->next;
	}
	ret_str[j] = '\0';
	ft_strdupgnl_lstfree(NULL, 0, lst_first, 0);
	return (ret_str);
}

bool	ft_get_next_buf(char buf[BUFFER_SIZE], t_list *lst_first,
		bool *end_flag, ssize_t *read_byte)
{
	ssize_t	i;
	ssize_t	j;

	*end_flag = 0;
	i = 0;
	j = -1;
	if (*read_byte == 0)
		return (true);
	while (buf[i] != '\n' && i < BUFFER_SIZE && i < *read_byte)
		i += 1;
	if (buf[i] == '\n')
	{
		*end_flag = 1;
		i += 1;
	}
	*read_byte = *read_byte - i;
	if (ft_lst_append(i, buf, lst_first) == false)
		return (false);
	while (i + ++j < BUFFER_SIZE)
		buf[j] = buf[i + j];
	if (BUFFER_SIZE!=j)
		buf[j] = '\0';
	return (true);
}
