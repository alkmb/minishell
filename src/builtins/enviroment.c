/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 01:20:03 by akambou           #+#    #+#             */
/*   Updated: 2024/04/13 02:22:53 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_environment(char **env)
{
	while (*env != NULL)
	{
		ft_printf("declare -x %s\n", *env);
		env++;
	}
}

char	**create_new_environment(t_shell *shell, int j, char *name, char *value)
{
	int		k;
	char	**new_environ;

	new_environ = malloc((j + 2) * sizeof(char *));
	k = 0;
	while (k < j)
	{
		new_environ[k] = ft_strdup(shell->environ[k]);
		++k;
	}
	new_environ[j] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	ft_strlcpy(new_environ[j], name, ft_strlen(name) + 1);
	ft_strlcat(new_environ[j], "=", ft_strlen(name) + 2);
	ft_strlcat(new_environ[j], value, ft_strlen(name) + ft_strlen(value) + 2);
	new_environ[j + 1] = NULL;
	return (new_environ);
}

void	add_to_environment(t_shell *shell)
{
	char	*name;
	char	*value;
	int		j;
	int		i;

	i = 1;
	name = ft_strtok(shell->data->args[i], "=");
	while (shell->data->args[i] != NULL)
	{
		value = ft_strtok(NULL, "=");
		if (value == NULL)
			value = "";
		j = 0;
		while (shell->environ[j] != NULL)
			j++;
		i++;
	}
	shell->environ = create_new_environment(shell, j, name, value);
}

int	find_env_var(t_shell *shell)
{
	int		i;
	char	*name;
	char	*env_var;

	i = 0;
	while (shell->environ[i])
	{	
		env_var = ft_strdup(shell->environ[i]);
		name = ft_strtok(env_var, "=");
		if (ft_strcmp(name, shell->data->args[1]) == 0)
		{
			free(env_var);
			return (i);
		}
		free(env_var);
		i++;
	}
	return (-1);
}

void	unset_env_var(t_shell *shell, int index)
{
	int		j;
	char	*tmp;

	j = index;
	tmp = shell->environ[j];
	while (shell->environ[j])
	{
		shell->environ[j] = shell->environ[j + 1];
		j++;
	}
	free(tmp);
}
