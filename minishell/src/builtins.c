/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/01/22 03:16:00 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_echo(char **args)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

int	cmd_cd(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
		{
			perror(args[1]);
			return (127);
		}
	}
	else
		chdir(getenv("HOME"));
	return (0);
}

int	cmd_pwd(void)
{
	char	cwd[1024];

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
	int	i;

	if (args[1] != NULL)
	{
		i = 0;
		while (environ[i])
		{
			if (ft_strncmp(environ[i], args[1], ft_strlen(args[1])) == 0 \
				&& environ[i][ft_strlen(args[1])] == '=')
			{
				while (environ[++i])
					environ[i] = environ[i + 1];
				break ;
			}
			i++;
		}
	}
	else
	{
		ft_printf("Usage: unset variable_name\n");
		return (127);
	}
	return (0);
}

int	cmd_export(char **args)
{
	char	**env;

	env = environ;
	if (args[1] == NULL)
	{
		while (*env != NULL)
		{
			ft_printf("declare -x %s\n", *env);
			env++;
		}
		return (0);
	}
	else
		return (127);
}
