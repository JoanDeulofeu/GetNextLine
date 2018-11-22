/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:49:31 by jgehin            #+#    #+#             */
/*   Updated: 2018/11/22 16:20:51 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

char	*ft_memnmove(char *line, char *buff, int c, int n)
{
	int		u;
	char	*l1;
	char	*l2;

	l2 = ft_memchr(buff, c, n);
	u = l2 == NULL ? (n + 1) : (l2 - buff + 1);
	l2 = ft_memalloc(u);
	ft_memset(l2, 'p', u);
	ft_strncpy(l2, buff, u);
	l2[u - 1] = '\0';
	l1 = !line ? l2 : ft_memalloc(ft_strlen(line) + ft_strlen(l2));
	if (line)
		ft_memmove(l1, line, ft_strlen(line));
	return (line = !line ? l2 : ft_strncat(l1, l2, ft_strlen(l1)));
}

int		get_next_line(const int fd, char **line)
{
	char	buff[BUFF_SIZE];

	read(fd, buff, BUFF_SIZE);
	*line = ft_memnmove(*line, buff, '\n', BUFF_SIZE);
	return (0);
}
