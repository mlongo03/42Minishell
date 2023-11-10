/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:31 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/04 19:17:32 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	res = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (res == NULL)
		return (NULL);
	while (s[i])
	{
		res[i] = (char) f(i, s[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}
