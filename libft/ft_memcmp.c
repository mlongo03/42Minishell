/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:15:09 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/04 19:15:11 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n && ((char *) s1)[i] == ((char *) s2)[i])
		i++;
	if (i == n)
		i--;
	return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
}
