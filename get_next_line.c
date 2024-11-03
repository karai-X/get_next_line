/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:15:20 by karai             #+#    #+#             */
/*   Updated: 2024/11/03 23:15:14 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE];
	static ssize_t	read_byte;
	t_list			lst_first;
	bool			end_flag;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	lst_first.next = NULL;
	if (ft_get_next_buf(buf, &lst_first, &end_flag, &read_byte) == false)
		return (ft_strdupgnl_lstfree(NULL, 0, &lst_first, 0));
	if (end_flag)
		return (ft_lst_combine(&lst_first));
	while (1)
	{
		read_byte = read(fd, (void *)buf, BUFFER_SIZE);
		if (read_byte == -1)
			return (ft_strdupgnl_lstfree(NULL, 0, &lst_first, 0));
		if (read_byte == 0)
			break ;
		if (ft_get_next_buf(buf, &lst_first, &end_flag, &read_byte) == false)
			return (ft_strdupgnl_lstfree(NULL, 0, &lst_first, 0));
		if (end_flag)
			return (ft_lst_combine(&lst_first));
	}
	return (ft_lst_combine(&lst_first));
}

// #include <fcntl.h>
// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char	*line;
// 	int		fd;

// 	fd = open("test.txt", O_RDONLY);
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
