/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:02:21 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/22 12:10:24 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "../libft/libft.h"

char	*expand_res(char *current)
{
	char	*res;

	if (!current)
	{
		res = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		return (res);
	}
	res = (char *)ft_calloc(1, (ft_strlen(current) + BUFFER_SIZE) + 1);
	ft_memcpy(res, current, ft_strlen(current));
	free(current);
	return (res);
}

void	load_res(char *res, char *buf)
{
	int	i;

	i = 0;
	if (!res[0] && !buf[0])
		return ;
	while (*res)
		res++;
	while (buf[i])
	{
		res[i] = buf[i];
		if (res[i++] == '\n')
		{
			ft_memcpy(buf, &buf[i], BUFFER_SIZE - i);
			ft_bzero(buf + BUFFER_SIZE - i, i);
			return ;
		}
	}
	ft_bzero(buf, BUFFER_SIZE);
}

char	*get_next_line(int fd)
{
	static char	buf[4096][BUFFER_SIZE];
	char		*res;
	int			countread;

	countread = 0;
	if (fd < 0 || fd >= 4096 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	res = expand_res(NULL);
	load_res(res, buf[fd]);
	if (!*buf[fd])
		countread = read(fd, buf[fd], BUFFER_SIZE);
	while (countread > 0 && res[ft_strlen(res) - 1] != '\n')
	{
		res = expand_res(res);
		load_res(res, buf[fd]);
		if (res[ft_strlen(res) - 1] == '\n')
			break ;
		countread = read(fd, buf[fd], BUFFER_SIZE);
	}
	if (res && !*res)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
