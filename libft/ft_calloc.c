/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:12:39 by mlongo            #+#    #+#             */
/*   Updated: 2023/04/04 19:12:41 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	int		len;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	len = count * size;
	res = (void *) malloc(len);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, len);
	return (res);
}
