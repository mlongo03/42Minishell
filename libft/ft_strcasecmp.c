/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:15:53 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/08 17:48:51 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcasecmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (ft_tolower(*str1) != ft_tolower(*str2))
		{
			return (ft_tolower(*str1) - ft_tolower(*str2));
		}
		str1++;
		str2++;
	}
	return (ft_tolower(*str1) - ft_tolower(*str2));
}
