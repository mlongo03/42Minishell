/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:51:51 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/09 15:56:28 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parentheses(char *s, int *i)
{
	if (*i != 0)
	{
		if (s[*i - 2] == '(' && check_number(s))
			return (1);
		// if (!((s[*i - 2] == '&' && s[*i - 3] == '&') || (s[*i - 2] == '|' && s[*i - 3] == '|') || (s[*i - 2] == '|' && s[*i - 3] == ' ')))
		// 	return (0);
		// printf("\n%c\n%c\n%c\n%c\n", s[*i - 2], s[*i - 3], s[*i + 2], s[*i + 3]);
		if (is_op(&s[*i - 2]) || is_op(&s[*i - 3]))
		{
			if (!is_op(&s[*i + 2]))
				return (1);
		}
		return (0);
	}
	if (check_number(s))
		return (1);
	return (0);
}

int	check_operator(char *s, int *i)
{
	// if (s[*i] == '>' || s[*i] == '<')
	// {
	// 	if ((s[*i] == s[*i + 1] && s[*i + 2] == ' ' && s[*i + 3] != '>' && s[*i + 4] != '<') || (s[*i + 1] == ' ' && s[*i + 2] != '>' && s[*i + 3] != '<'))
	// 		return (1);
	// }
	if (s[*i + 1] == 0 || s[*i + 2] == 0 || *i == 0 || is_op(&s[0]) || is_double(s, i))
		return (0);
	return (1);
	// if (is_red(&s[*i]))
	// {}
	// if ((not_op(&s[*i - 3]) || not_op(&s[*i - 2])) && s[*i - 1] == ' ')
	// {
	// 	if (s[*i] == s[*i + 1] && s[*i + 2] == ' ' && not_op(&s[*i + 3]))
	// 	{
	// 		(*i)++;
	// 		return (1);
	// 	}
	// 	if (s[*i] == '|' && s[*i + 1] == ' ' && not_op(&s[*i + 2]))
	// 		return (1);
	// }
	// return (0);
}

int	check_quote(char *s)
{
	int		i;
	int		count;
	char	c;

	i = -1;
	count = 0;
	c = 0;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i];
			i++;
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
			if (s[i] == c)
				count--;
		}
	}
	return (counter(count));
}

int	check_number(char *s)
{
	int		i;
	int		count;
	char	c;

	i = -1;
	count = 0;
	c = 0;
	while (s[++i])
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			c = s[i];
			i++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == '(')
			count++;
		if (s[i] == ')')
			count--;
	}
	return (counter(count));
}

// int check_quote(char *s)
// {
// 	int i;
// 	int count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '"')
// 		{
// 			i++;
// 			count++;
// 			while (s[i] != '"' && s[i] != '\0')
// 				i++;
// 			if (s[i] == '"')
// 			count--;
// 		}
// 		if (s[i] == '\'')
// 		{
// 			i++;
// 			count++;
// 			while (s[i] != '\'' && s[i] != '\0')
// 				i++;
// 			if (s[i] == '\'')
// 			count--;
// 		}
// 		i++;
// 	}
// 	return (counter(count));
// }
