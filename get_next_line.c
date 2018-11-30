/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:49:31 by jgehin            #+#    #+#             */
/*   Updated: 2018/11/30 17:27:42 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "get_next_line.h"
#include <stdio.h>

void	*ft_save_in_list(char *buff, int fd, t_list *list)
{
	char	*s;
	char	*tmp;
	int		len;
	t_list	*tmplst;

	tmp = ft_memchr(buff, '\n', BUFF_SIZE);
	len = tmp == NULL ? 2 : BUFF_SIZE - (tmp - buff);
	tmp = (tmp == NULL) ? buff : tmp;
	s = ft_memalloc(len);
	ft_strncpy(s, ++tmp, len);
	s[len - 1] = '\0';
	if (!list)
	{
		list = ft_lstnew(s, len);
		list->content_size = (size_t)fd;
		return (list);
	}
	tmplst = list;
	while (tmplst->content_size != (size_t)fd && tmplst->next != NULL)
		tmplst = tmplst->next;
	if (tmplst->content_size == (size_t)fd)
		tmplst->content = s;
	else
	{
		tmplst->next = ft_lstnew(s, len);
		tmplst->next->content_size = (size_t)fd;
	}
	return (list);
}

int		ft_alloc_line(char **line, char *buff)
{
	char	*tmp;
	int		len;

	tmp = ft_memchr(buff, '\n', BUFF_SIZE);
	if (tmp == buff)
		return (0);
	len = tmp == NULL ? (BUFF_SIZE + 1) : (tmp - buff + 1);
	tmp = ft_memalloc(len);
	ft_strncpy(tmp, buff, len - 1);
	tmp[len - 1] = '\0';
	*line = (**line != '\0') ? ft_strjoin(*line, tmp) : ft_strdup(tmp);
	return (len);
}

int		ft_check(char **line, t_list *list, const int fd, char *buff)
{
	t_list		*tmp;
	char		*c;

	tmp = NULL;
	if (list)
		tmp = list;
	while (tmp)
	{
		c = strdup(tmp->content);
		if (tmp->content_size == (size_t)fd)
		{
			if (*c != '\n')
				*line = strdup(tmp->content);
			else
			{
				ft_memmove(buff, tmp->content, ft_strlen(tmp->content) + 1);
				return (1);
			}
		}
		tmp = tmp->next;
		free(c);
	}
	return (0);
}
/*
   t_list	*ft_is_end(int res, t_list *list, char *buff, const int fd)
   {
   t_list		*tmplst;
   int 		i;

   i = -1;
   if (res != BUFF_SIZE)
   {
   tmplst = list;
   while (tmplst->content_size != (size_t)fd && tmplst->next != NULL)
   tmplst = tmplst->next;
   ft_memmove(buff, tmplst->content, ft_strlen(tmplst->content) + 1);
   }
   return (list);
   }*/

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE];
	int				u;
	static t_list	*list;
	int				res;

	if (!line || fd == -1)
		return (-1);
	u = BUFF_SIZE + 1;
	*line = ft_strdup("");
	if (ft_check(line, list, fd, buff) == 1)
	{
		list = ft_save_in_list(buff, fd, list);
		*line = ft_strdup("");
		return (1);
	}
	while (--u == BUFF_SIZE)
	{
		res = read(fd, buff, BUFF_SIZE);
		u = ft_alloc_line(line, buff);
		if (res < BUFF_SIZE)
			return (0);
	}
	list = ft_save_in_list(buff, fd, list);
	return (1);
}
