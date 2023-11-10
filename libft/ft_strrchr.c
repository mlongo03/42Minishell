/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:51 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/04 19:17:53 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (((unsigned char *) s)[i] == (unsigned char) c)
			return ((char *)(s + i));
		i--;
	}
	if (i)
		return (0);
	return ((char *)(s + i));
}
