/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:17 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 15:12:33 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (ft_strlen(src));
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dstsize)
		dst[i] = 0;
	while (src[i])
		i++;
	return (i);
}

char	*i_hate_this_strcpy_for_apix(char *dst, char *src)
{
	int		i;
	int		j;

	j = 1;
	i = 0;
	dst = malloc((ft_strlen(src) + 2) * sizeof(char));
	ft_memset(dst, 0, ft_strlen(src) + 2);
	dst[0] = '\"';
	while (src[i] && src[i + 1] != '\'')
	{
		dst[j] = src[i + 1];
		i++;
		j++;
	}
	dst = ft_strjoin_damn_you_leaks(dst, "\"");
	return (dst);
}
