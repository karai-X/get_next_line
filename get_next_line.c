/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:15:20 by karai             #+#    #+#             */
/*   Updated: 2024/11/01 17:35:31 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char	*ft_strdup_for_gnl(const char *s, size_t src_len)
{
	char	*copy_src;
	size_t	i;

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

void	ft_lst_free(t_list *lst_first)
{
	t_list	*ptr;

	while (lst_first->next != NULL)
	{
		ptr = lst_first->next->next;
		free(lst_first->next->content);
		free(lst_first->next);
		lst_first->next = ptr;
	}
}

bool	ft_lst_append(size_t read_byte, char *input_str, t_list *lst_first)
{
	t_list	*ptr;

	if (lst_first->next == NULL)
	{
		lst_first->next = (t_list *)malloc(sizeof(t_list));
		if (lst_first->next == NULL)
			return (false);
		lst_first->next->content = ft_strdup_for_gnl(input_str, read_byte);
		if (lst_first->next->content == NULL)
			return (false);
		lst_first->next->next = NULL;
		lst_first->next->length = read_byte;
	}
	else
	{
		ptr = lst_first->next;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = (t_list *)malloc(sizeof(t_list));
		if (ptr->next == NULL)
			return (false);
		ptr->next->content = ft_strdup_for_gnl(input_str, read_byte);
		if (ptr->next->content == NULL)
			return (false);
		ptr->next->length = read_byte;
		ptr->next->next = NULL;
	}
	return (true);
}

char	*ft_lst_combine(t_list *lst_first)
{
	size_t	i;
	t_list	*ptr;
	size_t	size;
	char	*ret_str;
	size_t	j;

	size = 0;
	ptr = lst_first->next;
	while (ptr != NULL)
	{
		if (SIZE_MAX - size - 1 < ptr->length)
			return (NULL);
		size += ptr->length;
		ptr = ptr->next;
	}
	if (size == 0)
	{
		ft_lst_free(lst_first);
		return (NULL);
	}
	ret_str = (char *)malloc(sizeof(char) * (size + 1));
	if (ret_str == NULL)
		return (NULL);
	ptr = lst_first->next;
	j = 0;
	while (ptr != NULL)
	{
		i = 0;
		while (i < ptr->length)
		{
			ret_str[j] = ptr->content[i];
			i += 1;
			j += 1;
		}
		ptr = ptr->next;
	}
	ret_str[j] = '\0';
	ft_lst_free(lst_first);
	return (ret_str);
}

bool	ft_get_next_buf(char buf[BUFFER_SIZE], t_list *lst_first,
		bool *end_flag)
{
	size_t	i;
	size_t	j;

	*end_flag = 0;
	i = 0;
	j = 0;
	while (buf[i] != '\0' && buf[i] != '\n' && i < BUFFER_SIZE)
		i += 1;
	if (buf[i] == '\n')
	{
		*end_flag = 1;
		i += 1;
	}
	if (ft_lst_append(i, buf, lst_first) == false)
		return (false);
	while (i + j < BUFFER_SIZE)
	{
		buf[j] = buf[i + j];
		j += 1;
	}
	while (j < BUFFER_SIZE)
		buf[j++] = 0;
	return (true);
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	int			read_byte;
	t_list		lst_first;
	char		*ret_str;
	bool		end_flag;

	if (BUFFER_SIZE == 0)
		return (NULL);
	lst_first.next = NULL;
	ft_get_next_buf(buf, &lst_first, &end_flag);
	if (end_flag)
		return (ft_lst_combine(&lst_first));
	read_byte = 1;
	while (read_byte > 0)
	{
		read_byte = read(fd, (void *)buf, BUFFER_SIZE);
		if (read_byte == -1)
		{
			ft_lst_free(&lst_first);
			return (NULL);
		}
		ft_get_next_buf(buf, &lst_first, &end_flag);
		if (end_flag)
			return (ft_lst_combine(&lst_first));
	}
	ret_str = ft_lst_combine(&lst_first);
	return (ret_str);
}

// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("text.txt", O_RDONLY);
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (!line)
// 		{
// 			break ;
// 		}
// 		printf("%s", line);
// 		printf("length %ld\n", strlen(line));
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
