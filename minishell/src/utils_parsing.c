/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 01:47:05 by akambou           #+#    #+#             */
/*   Updated: 2024/02/16 11:37:19 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_environment(char **environment, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(environment[i]);
		i++;
	}
	free(environment);
}

void	chose_command(char *commands[], int n)
{
	if (n < 0)
		return ;
	else
		chose_pipe(commands, n);
}

void	initialize_expansion_data(t_expansiondata *expansionData, \
char **commands, int i, int *is_malloced)
{
	expansionData->commands = commands;
	expansionData->i = i;
	expansionData->j = 0;
	expansionData->is_malloced = is_malloced;
}

void	free_malloced_commands(char **commands, int *is_malloced, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (is_malloced[j])
			free(commands[j]);
		j++;
	}
}
