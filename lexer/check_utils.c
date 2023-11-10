/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:54:51 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/09 15:55:40 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	counter(int count)
{
	if (count != 0)
		return (0);
	return (1);
}

int	is_op(char *c)
{
	if ((c[0] == '|' && c[1] == '|')
		|| (c[0] == '&' && c[1] == '&') || (c[0] == '|' && c[1] == ' ')
		|| (c[0] == '|' && c[1] == 0))
		return (1);
	return (0);
}

int	is_red(char *c)
{
	if ((c[0] == '<' && c[1] == '<') || (c[0] == '>' && c[1] == '>')
		|| (c[0] == '<' && c[1] == ' ') || (c[0] == '>' && c[1] == ' '))
		return (1);
	return (0);
}

int	is_op_or_red(char *s, int *i)
{
	if (is_op(&s[*i]) || is_red(&s[*i]))
		return (1);
	return (0);
}

int	is_one_char(char *c)
{
	if ((c[0] == '|' && c[1] == ' ') || (c[0] == '&' && c[1] == ' ')
		|| (c[0] == '<' && c[1] == ' ') || (c[0] == '>' && c[1] == ' '))
		return (1);
	return (0);
}

int	is_two_char(char *c)
{
	if ((c[0] == '|' && c[1] == '|') || (c[0] == '&' && c[1] == '&')
		|| (c[0] == '<' && c[1] == '<') || (c[0] == '>' && c[1] == '>'))
		return (1);
	return (0);
}

int	is_double(char *s, int *i)
{
	if (is_op(&s[*i]) && is_one_char(&s[*i]))
		if (is_op(&s[*i + 2]))
			return (1);
	if (is_op(&s[*i]) && is_two_char(&s[*i]))
		if (is_op(&s[*i + 3]))
			return (1);
	if (is_red(&s[*i]) && is_one_char(&s[*i]))
		if (is_red(&s[*i + 2]) || is_op(&s[*i + 2]))
			return (1);
	if (is_red(&s[*i]) && is_two_char(&s[*i]))
		if (is_red(&s[*i + 3]) || is_op(&s[*i + 3]))
			return (1);
	return (0);
}
