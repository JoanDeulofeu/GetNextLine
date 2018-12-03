/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:01:00 by jgehin            #+#    #+#             */
/*   Updated: 2018/12/03 13:41:36 by jgehin           ###   ########.fr       */
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
	ft_bzero(list->buff, BUFF_SIZE);
	list->fd = fd;
	list->next = NULL;
	return (list);
}

int		ft_alloc_line(char **line, t_glist *list, int i)
{
	char	*tmp;
	int		len;

	len = 0;
	if (i == 1)
		list->i = read(list->fd, list->buff, BUFF_SIZE);
	if (list->i == 0)
		return (-42);
	if (i >= 1)
	{
		tmp = ft_memchr(list->buff, '\n', ft_strlen(list->buff));
		if (list->buff[0] == '\n')
			return (0);
		len = tmp == NULL ? BUFF_SIZE + 1 : (tmp - list->buff) + 1;
		tmp = ft_memalloc(len);
		ft_strncpy(tmp, list->buff, len - 1);
		*line = (**line != '\0') ? ft_strjoin(*line, tmp) : ft_strdup(tmp);

		if (len != BUFF_SIZE + 1)
		{
			printf("test\n");
			tmp = ft_memchr(list->buff, '\n', ft_strlen(list->buff));
			list->save = ft_memalloc((ft_strlen(list->buff) - len) + 1);
			ft_strncpy(list->save, ++tmp, ft_strlen(list->buff) - len);
			list->save = ft_strdup(list->buff);
		}
	}
	return (len);
}

int		get_next_line(const int fd, char **line)
{
	int		n;
	int		i;
	static t_glist	*list;

	if (!line || fd == -1)
		return (-1);
	list = !list ?  ft_glistnew("\0", fd) : list;
	if (list->save[0] != '\0' && BUFF_SIZE != 1)
	{
		*list->buff = &list->save;
		free(list->save);
	}
	n = (ft_memchr(list->save, '\n', BUFF_SIZE) == NULL) ? 1 : 2;
	i = ft_alloc_line(line, list, n);
	while (i == BUFF_SIZE + 1)
	{
		if (i == 0)
		{
			*line = ft_strdup("");
			list->buff[0] = '\0';
			while (++i > BUFF_SIZE)
				list->buff[i-1] = list->buff[i];
			return (1);
		}
		i = ft_alloc_line(line, list, n);
		if (list->i == -42)
			return (0);
	}
	return (1);
}
