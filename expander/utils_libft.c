/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:51:50 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/06 18:40:29 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_strncat(char **dest, char c, int nb)
{
	size_t	current_len;
	int		i;

	if (*dest != NULL)
		current_len = ft_strlen(*dest);
	else
		current_len = 0;
	(*dest) = (char *)ft_realloc(*dest, sizeof(char),
			current_len, current_len + nb + 1);
	if (*dest == NULL)
		return ;
	i = 0;
	while (i < nb)
	{
		(*dest)[current_len + i] = c;
		i++;
	}
	(*dest)[current_len + nb] = '\0';
}

char	*handle_apix_case(char *ret)
{
	ret = ft_realloc(ret, sizeof(char), 2, 3);
	ret[0] = '\'';
	ret[1] = '\'';
	ret[2] = '\0';
	return (ret);
}
