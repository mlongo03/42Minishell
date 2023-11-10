/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:36:48 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/08 16:37:11 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_env(const char *input, const char *env)
{
	while (*env != '=' && (*input != ' ' || *input != '$'))
	{
		if (*input != *env)
			return (1);
		input++;
		env++;
	}
	return (*env != '=' || *input != '\0');
}
