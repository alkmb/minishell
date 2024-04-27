/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/04/27 01:38:05 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_echo(t_shell *shell, int i)
{
	char	*name;
	char	*value;
	int		index;

	index = find_env_var(shell);
	if (index != -1)
	{
		value = ft_strchr(shell->environ[index], '=') + 1;
		ft_printf("%s\n", value);
	}
	if (ft_strcmp(shell->data->args[i], "$?") == 0)
		ft_printf("%d", shell->status);
	else if (index == -1)
	{
		ft_printf("%s", shell->data->args[i]);
		if (shell->data->args[i + 1] != NULL)
			ft_printf(" ");
	}
}

int	cmd_echo(t_shell *shell)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	if (shell->data->args[i] != NULL
		&& ft_strcmp(shell->data->args[i], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	while (shell->data->args[i] != NULL)
	{
		print_echo(shell, i);
		i++;
	}
	if (!newline && ft_strcmp(shell->data->args[0], "$?") != 0)
		ft_printf("\n");
	return (0);
}

int	cd_with_args(t_shell *shell, int len)
{
	char	*path;

	if (shell->data->args[1][0] == '~')
	{
		path = malloc(ft_strlen(getenv("HOME")) + len);
		ft_strlcpy(path, getenv("HOME"), 5);
		ft_strlcat(path, shell->data->args[1] + 1, \
		ft_strlen(getenv("HOME")) + len + 1);
	}
	else
		path = shell->data->args[1];
	if (chdir(path) != 0)
	{
		if (shell->data->args[1][0] == '~')
			free(path);
		return (127);
	}
	if (shell->data->args[1][0] == '~')
		free(path);
	return (0);
}

int	cmd_cd(t_shell *shell)
{
	int		len;

	len = ft_strlen(shell->data->args[1]);
	if (shell->data->args[1] != NULL)
		return (cd_with_args(shell, len));
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
