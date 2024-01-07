/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/01/07 16:46:39 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_rev(char **args)
{
	if (args[1] != NULL)
	{
		char *str = args[1];
		int len = strlen(str);
		for (int i = len - 1; i >= 0; i--)
			printf("%c", str[i]);
		printf("\n");
	}
	else
	{
		char buffer[1024];
		while (fgets(buffer, sizeof(buffer), stdin) != NULL)
		{
			int len = strlen(buffer);
			for (int i = len - 1; i >= 0; i--)
				printf("%c", buffer[i]);
			printf("\n");
		}
	}
}
#include <dirent.h>

void cmd_ls()
{
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			printf("%s\n", dir->d_name);
		}
		closedir(d);
	}
}
void cmd_echo(char **args)
{
	int i = 1;
	while (args[i] != NULL)
	{
		ft_printf("%s ", args[i]);
		i++;
	}
	ft_printf("\n");
}

void cmd_cd(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
		{
			perror(args[1]);
		}
	}
	else
		chdir(getenv("HOME"));
}

void cmd_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void cmd_unset(char **args)
{
	if (args[1] != NULL)
	{
		int i = 0;
		while (environ[i])
		{
			if (ft_strncmp(environ[i], args[1], ft_strlen(args[1])) == 0 \
				&& environ[i][ft_strlen(args[1])] == '=')
			{
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				break;
			}
			i++;
		}
	}
	else
		ft_printf("Usage: unset variable_name\n");
}

void cmd_export(char **args)
{
	if (args[1] == NULL)
	{
		char **env = environ;
		while(*env != NULL)
		{
			ft_printf("declare -x %s\n", *env);
			env++;
		}
	}
}
