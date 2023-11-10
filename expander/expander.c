/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/06 18:50:34 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_logic_norm(char *input, char **ret, char quote, t_mini *shell_data)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == quote)
		{
			i++;
			break ;
		}
		else if (input[i] == '$' && quote == '"')
			*ret = manage_dollar_norm(input, &i, *ret, shell_data);
		else
			ft_strncat(ret, input[i++], 1);
	}
	return (i);
}

char	*expander(t_mini *shell_data, char *input)
{
	char	*ret;
	int		i;
	char	quote;

	i = 0;
	ret = ft_calloc(1, sizeof(char));
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			ret = manage_dollar_norm(input, &i, ret, shell_data);
		else if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			i += quote_logic_norm(&input[i], &ret, quote, shell_data);
		}
		else
			ft_strncat(&ret, input[i++], 1);
	}
	if (ret && ft_strlen(ret) <= 3 && ft_strchr(ret, '\''))
		ret = handle_apix_case(ret);
	free(input);
	return (ret);
}
