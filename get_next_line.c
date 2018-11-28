/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:49:31 by jgehin            #+#    #+#             */
/*   Updated: 2018/11/28 18:33:48 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

void	*ft_save_in_list(char *buff, int fd, t_list *list)
{
	char	*s;
	char	*tmp;
	int		len;
	t_list	*tmplst;

	tmp = ft_memchr(buff, '\n', BUFF_SIZE);
	len = tmp == NULL ? 1 : BUFF_SIZE - (tmp - buff);
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
	len = tmp == NULL ? (BUFF_SIZE + 1) : (tmp - buff + 1);
	tmp = ft_memalloc(len);
	ft_strncpy(tmp, buff, len);
	tmp[len - 1] = '\0';
	*line = (**line != '\0') ? ft_strjoin(*line, tmp) : ft_strdup(tmp);
	return (len);
}

void	ft_check(char **line, t_list *list, const int fd)
{
	t_list		*tmp;

	tmp = NULL;
	if (list)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->content_size == (size_t)fd)		
				*line = strdup(tmp->content);
			tmp = tmp->next;
		}
	}
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE];
	int				u;
	static t_list	*list;
	int				res;

	u = BUFF_SIZE;
	*line = ft_strdup("");
	if (fd == -1)
		return (-1);
	ft_check(line, list, fd);
	while (u == BUFF_SIZE)
	{
		res = read(fd, buff, BUFF_SIZE);
		if (buff[0] == '\n' || *line[0] == '\n')
		{
			list = ft_save_in_list(buff, fd, list);
			*line = ft_strdup("");
			return (1);
		}
//		res = read(fd, buff, BUFF_SIZE);
		u = ft_alloc_line(line, buff);
		if (res < BUFF_SIZE)
			return(0);
		u--;
//		printf("%s\n", "???"); 
	}
	list = ft_save_in_list(buff, fd, list);	
	return (1);
}
