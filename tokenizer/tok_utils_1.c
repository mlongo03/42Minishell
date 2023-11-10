/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:30 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 16:26:17 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_matrix(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (0);
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= '\t' && c <= '\r'));
}

char	*ft_strpbrk(char *str, char *set)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strbash_control(char *str)
{
	if (str[0] == '|' || (str[0] == '&' && str[1] == '&')
		|| str[0] == '<' || str[0] == '>'
		|| str[0] == '(' || str[0] == ')' || str[0] == '`'
		|| str[0] == '\\' || ft_isspace(str[0]))
		return (&str[0]);
	return (NULL);
}

int	ft_stralnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}
