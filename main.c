/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgehin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:16:48 by jgehin            #+#    #+#             */
/*   Updated: 2018/11/26 18:54:06 by jgehin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int		main(int ac, char **av)
{
	int		fd;
	char	*line;
	int		i;
	int 	num = 1;

	i = 2;
	if (ac == 8)
		i = 1;
		fd = open(av[1], O_RDONLY);
	while (i != 0)
	{
		i = get_next_line(fd, &line);
		printf("%s\n", line);
		printf("%s", "@@@@@@@@   LIGNE ");
		printf("%d", num++);
		printf("%s\n", "   @@@@@@@");
	}
	return (0);
}
