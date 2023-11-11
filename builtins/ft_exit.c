/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:37:44 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/11 16:02:39 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isstrnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_conditions(char **args, int exit_value, int len_args)
{
	if (ft_isstrnum(args[0]))
	{
		if (len_args == 1)
		{
			exit_value = ft_atoi(args[0]);
			while (exit_value >= 256)
				exit_value -= 256;
			while (exit_value < 0)
				exit_value += 256;
			printf("exit\n");
			free_exit(exit_value);
		}
		else
		{
			ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			g_last_exit_status_cmd = 1;
		}
	}
	else
	{
		p_error("exit\nminishell: exit: ",
			args[0], ": numeric argument required\n");
		free_exit(2);
	}
}

void	ft_exit(char **args)
{
	int	len_args;
	int	exit_value;

	len_args = 0;
	exit_value = 0;
	if (args)
		while (args[len_args])
			len_args++;
	if (len_args == 0)
	{
		printf("exit\n");
		free_exit(0);
	}
	else
		exit_conditions(args, exit_value, len_args);
}
