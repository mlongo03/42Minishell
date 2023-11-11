/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:34:36 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/11 12:43:34 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	pwd[4096];

	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
	else
		printf("minishell : the path is broken use 'cd <path>' or 'cd ..'\n");
	return (0);
}

static int	echo_case(char **command_line)
{
	if (!command_line)
		return (1);
	else if (!command_line[1] && !ft_strcmp(command_line[0], "-n"))
		return (2);
	return (0);
}

static void	echo_printer(char **command_line, int flag, int mat_size, int i)
{
	if (flag == 1)
		i++;
	while (command_line[mat_size])
		mat_size++;
	while (command_line[++i])
	{
		printf("%s", command_line[i]);
		if (i < mat_size - 1)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
}

static int	flag_checker(char **command_line, int flag)
{
	int	n_counter;

	n_counter = 1;
	if (command_line[0][0] == '-' && command_line[0][1] == 'n')
	{
		flag = 1;
		while (command_line[0][++n_counter])
		{
			if (command_line[0][n_counter] != '\0'
				&& command_line[0][n_counter] != 'n')
				flag = 0;
		}
	}
	return (flag);
}

int	ft_echo(char **command_line)
{
	int	i;
	int	flag;
	int	mat_size;

	mat_size = 0;
	flag = 0;
	i = -1;
	if (echo_case(command_line) == 2)
		return (0);
	else if (echo_case(command_line) == 1)
	{
		printf("\n");
		return (0);
	}
	flag = flag_checker(command_line, flag);
	echo_printer(command_line, flag, mat_size, i);
	return (0);
}
