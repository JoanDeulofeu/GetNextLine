/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:49:31 by jgehin            #+#    #+#             */
/*   Updated: 2018/11/27 16:33:38 by jgehin           ###   ########.fr       */
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
	new->str = ft_memalloc(len);
	ft_strncpy(new->str, s, len);
	printf("%d\n", 444);
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

	printf("%d\n", 888);
	tmp = ft_memchr(buff, '\n', BUFF_SIZE);
	len = tmp == NULL ? 0 : BUFF_SIZE - ((tmp - buff) + 1);
	s = ft_memalloc(len);
	ft_strncpy(s, ++tmp, len);
	printf("%d\n", 222);
	s[len - 1] = '\0';
	if (!list)
	{
		list = ft_glst(s, len, fd);
		printf("%stest1\n", list->str); 
		return (list);
	}
	tmplst = list;
	while (tmplst->fd != fd && tmplst->next != NULL)
		tmplst = tmplst->next;
	if (tmplst->fd == fd)
		tmplst->str = s;
	else
		tmplst->next = ft_glst(s, len, fd);
//	tmplst = tmplst->next;			// en cas de multi fd
	printf("%s\n", tmplst->str);   
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
	printf("%d\n", 333);
	tmp[len - 1] = '\0';
	*line = (**line != '\0') ? ft_strjoin(*line, tmp) : ft_strdup(tmp);
	return (len);
}

void	ft_check(char **line, t_glist *list, const int fd)
{
	t_glist		*tmp;

	tmp = NULL;
	if (list)
	{
		tmp = list;
		while (tmp)
		{
			if (tmp->fd == fd)		
				*line = strdup(tmp->str);
			tmp = tmp->next;
		}
	}
}

int		get_next_line(const int fd, char **line)
{
	char			buff[BUFF_SIZE];
	int				u;
	static t_glist	*list;
	int				res;

	u = BUFF_SIZE;
	*line = ft_strdup("");
	ft_check(line, list, fd);
	while (u == BUFF_SIZE)
	{
		res = read(fd, buff, BUFF_SIZE);
		u = ft_alloc_line(line, buff);
		if (res < BUFF_SIZE)
			return(0);
	}
	list = ft_save_in_list(buff, fd, list);
	printf("%stest2\n", list->str); 
	return (1);
}
