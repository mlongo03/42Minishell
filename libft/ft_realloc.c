/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:30:26 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/01 10:45:52 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *p, size_t size, int dim, int new_dim)
{
	char		*new_p;
	size_t		i;

	new_p = (char *)malloc(size * new_dim);
	if (!new_p)
		return (NULL);
	i = 0;
	while (i < size * new_dim)
	{
		if (i < size * dim)
			new_p[i] = ((char *) p)[i];
		else
			new_p[i] = 0;
		i++;
	}
	free(p);
	return ((void *) new_p);
}
