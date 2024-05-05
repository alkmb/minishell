/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 21:51:02 by kmb               #+#    #+#             */
/*   Updated: 2024/04/08 06:34:04 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_malloced(char *commands[], int *is_malloced, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (is_malloced[j])
			free(commands[j]);
		j++;
	}
}

void	free_args(char **args)
{
	int	j;

	j = 0;
	while (args[j] != NULL)
		free(args[j++]);
	free(args);
	args = NULL;
}

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
