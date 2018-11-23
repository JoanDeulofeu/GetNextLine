/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:49:31 by jgehin            #+#    #+#             */
/*   Updated: 2018/11/23 17:06:51 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

void	ft_alloc_line(char **line, char *buff, int c, int n)
{
	int		u;
	char	*l1;
	char	*l2;

	l2 = ft_memchr(buff, c, n);
	u = l2 == NULL ? (n + 1) : (l2 - buff + 1);
	l2 = ft_memalloc(u);
	ft_strncpy(l2, buff, u);
	l2[u - 1] = '\0';
	l1 = line ? ft_strjoin(*line, l2) : l2;
	*line = ft_strdup(l1);
}

int		get_next_line(const int fd, char **line)
{
	char	buff[BUFF_SIZE];
	int		i;
	int		u;

	i = 1;
	line = NULL;
	while (((u = line ? ft_strlen(*line) : 0) + BUFF_SIZE) == BUFF_SIZE * i++)
	{
		read(fd, buff, BUFF_SIZE);
		ft_alloc_line(line, buff, '\n', BUFF_SIZE);
	}
	return (0);
}
