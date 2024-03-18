/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 00:41:41 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// COMMAND ECHO
int	cmd_echo(char **args)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	// CHECK IF -N FLAG IS PRESENT
	if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	// PRINT ARGUMENTS
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	// PRINT NEWLINE IF -N FLAG IS NOT PRESENT
	if (!newline)
		ft_printf("\n");
	return (0);
}

int	cmd_cd(char **args)
{
	char	*path;

	if (args[1] != NULL)
	{
		// CHANGE DIRECTORY TO HOME
		if (args[1][0] == '~')
		{
			path = malloc(ft_strlen(getenv("HOME")) + strlen(args[1]));
			ft_strlcpy(path, getenv("HOME"), 5);
			ft_strlcat(path, args[1] + 1, ft_strlen(getenv("HOME")) \
			+ ft_strlen(args[1]) + 1);
		}
		// CHANGE DIRECTORY TO PATH
		else
			path = args[1];
		if (chdir(path) != 0)
		{
			if (args[1][0] == '~')
				free(path);
			return (127);
		}
		if (args[1][0] == '~')
			free(path);
	}
	else
		chdir(getenv("HOME"));
	return (0);
}

int	cmd_pwd(void)
{
	char	cwd[1024];

	// PRINT CURRENT WORKING DIRECTORY
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (127);
	}
	return (0);
}

int	cmd_unset(char **args)
{
	int	index;

	// UNSET ENVIRONMENT VARIABLE
	if (args[1] != NULL)
	{
		index = find_env_var(args);
		if (index != -1)
		{
			unset_env_var(index);
		}
	}
	else
	{
		ft_printf("unset: not enough arguments\n");
		return (127);
	}
	return (0);
}

void	cmd_env(char **environ)
{
	ft_printf("%s\n", environ[1]);
}
