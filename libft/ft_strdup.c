/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:16:44 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/04 19:16:52 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;

	len = ft_strlen(s);
	res = malloc(len + 1);
	if (res == NULL)
		return (NULL);
	res[len] = 0;
	while (len--)
		res[len] = s[len];
	return (res);
}
