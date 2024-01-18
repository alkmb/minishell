/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:25:30 by kmb               #+#    #+#             */
/*   Updated: 2024/01/18 07:50:57 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**token_single_cmd(char *commands[], int n)
{
	int i = 0;
	char **args =(char **)malloc(MAX_ARGS * sizeof(char*));

	args[i] = ft_strtok(commands[n], " ");
	while (args[i] != NULL)
	{
		i++;
		args[i] = ft_strtok(NULL, " ");
	}
	args[i] = NULL;
	return args;
}
char	**token_pipe_cmd(char *commands[], int n)
{

	int i = 0;
	char **args =(char **)malloc(MAX_ARGS * sizeof(char*));
	char *saveptr;

	args[i] = ft_strtok_r(commands[n], " ", &saveptr);
	while (args[i] != NULL)
	{
		i++;
		args[i] = ft_strtok_r(NULL, " ", &saveptr);
	}
	args[i] = NULL;
	return args;
}
