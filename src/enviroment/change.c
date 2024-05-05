/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_environ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:10:16 by gprada-t          #+#    #+#             */
/*   Updated: 2024/04/27 01:38:36 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	i = 0;
	while (ft_isalpha(name[i]) || name[i] == '_')
		i++;
	if (name[i] != '\0' || name[0] == '\0')
		ft_printf("minishell: export: `%s': not a valid identifier\n", name);
	else
		shell->environ = create_new_environment(shell, j, name, value);
}
