/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 11:29:59 by jgehin            #+#    #+#             */
/*   Updated: 2018/12/03 14:58:27 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10

typedef struct		s_glist
{
	char			*save;
	int				rem;
	int				fd;
	int				i;
	struct s_glist	*next;
}					t_glist;
int		get_next_line(const int fd, char **line);

#endif
