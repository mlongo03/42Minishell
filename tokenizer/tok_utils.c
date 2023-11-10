/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:33 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 15:07:24 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*no_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		diff;

	diff = 0;
	i = 0;
	j = 0;
	res = ft_substr(str, 0, ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '"')
		{
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
			while (str[i] != '"')
				i++;
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
		}
		else if (str[i] == '\'')
		{
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
			while (str[i] != '\'')
				i++;
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
		}
	}
	res[i - (ft_strlen(str) - ft_strlen(res))] = 0;
	return (res);
}
