/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnlultime.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:07:37 by jgehin            #+#    #+#             */
/*   Updated: 2018/12/03 16:43:01 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

t_glist	*ft_glistnew(char *str, int fd)
{
	t_glist	*list;

	if (!(list = (t_glist*)malloc(sizeof(*list))))
		return (0);
	list->save = ft_strdup(str);
	list->rem = 0;
	list->fd = fd;
	list->next = NULL;
	return (list);
}

int		ft_alloc(char **line, t_glist *list)
{
	char	*tmp;
	char	*tmp2;
	int		len;

	tmp = ft_memchr(list->save, '\n', ft_strlen(list->save));
	if (tmp == NULL)
	{
		*line = strdup(list->save);
		return (0);
	}
	len = (tmp - list->save) + 1;
	tmp2 = ft_memalloc(len);
	ft_strncpy(tmp2, list->save, len - 1);
	tmp2[len - 1] = '\0';
	*line = ft_strdup(tmp2);

	tmp2 = ft_memalloc((ft_strlen(list->save) - len) + 1);
	ft_strncpy(tmp2, ++tmp, ft_strlen(list->save) - len);
	list->save = strdup(tmp2);
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_glist	*list;
	char			buff[BUFF_SIZE];
	int				i;

	list = (!list) ? ft_glistnew("\0", fd) : list;
	list->i = BUFF_SIZE;
	if (list->rem == 0)
	{
		while (list->i == BUFF_SIZE)
		{
			list->i = read(fd, buff, BUFF_SIZE);
			if (list->i != 0)
				ft_strjoin(list->save, buff);
		}
		list->rem = 1;
	}
	if ((i = ft_alloc(line, list)) == 0)
		return (0);
	return (1);
}
