/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karai <karai@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 12:38:42 by karai             #+#    #+#             */
/*   Updated: 2024/11/01 15:49:32 by karai            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// void	ft_lst_print(t_list *lst_first)
// {
// 	size_t	i;
// 	t_list	*ptr;

// 	ptr = lst_first->next;
// 	while (ptr != NULL)
// 	{
// 		i = 0;
// 		while (i < ptr->length)
// 		{
// 			write(1, &((ptr->content)[i]), 1);
// 			i += 1;
// 		}
// 		ptr = ptr->next;
// 	}
// }
