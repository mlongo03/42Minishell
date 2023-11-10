/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:04:32 by alessiolong       #+#    #+#             */
/*   Updated: 2023/08/20 12:06:43 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (1)
	{
		if (s1[i] == '\0' || s2[i] == '\0'
			|| s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
