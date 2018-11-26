/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:49:31 by jgehin            #+#    #+#             */
/*   Updated: 2018/11/26 16:58:13 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

t_glist	*ft_glst(char *s, int len, int fd)
{
	t_glist		*new;

	if (!(new = (t_glist*)malloc(sizeof(*new))))
		return (0);
	if (!(new->str = (char*)malloc(sizeof(*s) * len)))
		return (0);
	ft_strncpy(new->str, s, len);
	new->fd = fd;
	new->next = NULL;
	return (new);
}

void	*ft_save_in_list(char *buff, int fd, t_glist *list)
{
	char	*s;
	char	*tmp;
	int		len;
	t_glist	*tmplst;

	tmp = ft_memchr(buff, '\n', BUFF_SIZE);
	len = tmp == NULL ? 0 : BUFF_SIZE - (tmp - buff + 1);
	s = ft_memalloc(len);
	ft_strncpy(s, tmp, len);
	s[len - 1] = '\0';
	if (!list)
	{
		list = ft_glst(s, len, fd);
		return (list);
	}
	tmplst = list;
	while (tmplst->fd != fd && tmplst->next != NULL)
		tmplst = tmplst->next;
	if (tmplst->fd == fd)
		tmplst->str = s;
	else
		tmplst->next = ft_glst(s, len, fd);
	return (list);
}

void	ft_alloc_line(char **line, char *buff)
{
	char	*tmp;
	int		len;

	tmp = ft_memchr(buff, '\n', BUFF_SIZE);
	len = tmp == NULL ? (BUFF_SIZE + 1) : (tmp - buff + 1);
	tmp = ft_memalloc(len);
	ft_strncpy(tmp, buff, len);
	tmp[len - 1] = '\0';
	*line = (**line != '\0') ? ft_strjoin(*line, tmp) : ft_strdup(tmp);
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE];
	int				i;
	int				u;
	static t_glist	*list;
	t_glist			*tmp;

	i = 1;
	*line = ft_strdup("");
	if (list)
		tmp = list;
	while (tmp->next)
	{
		if (tmp->fd == fd)
			

	}
	while (((u = **line != '\0' ? ft_strlen(*line) : 0) + BUFF_SIZE) == BUFF_SIZE * i++)
	{
		u = read(fd, buff, BUFF_SIZE);
		ft_alloc_line(line, buff);
	}
	ft_save_in_list(buff, fd, list);
	return (u);
}
