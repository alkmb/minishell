/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:26 by kmb               #+#    #+#             */
/*   Updated: 2024/04/12 22:18:00 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_commandhistory	*create_history(void)
{
	t_commandhistory	*history;
	int					i;

	i = 0;
	history = malloc((sizeof(t_commandhistory)));
	history->index = 0;
	while (i < MAX_HISTORY - 1)
	{
		history->commands[i] = NULL;
		i++;
	}
	return (history);
}

void	add__history(t_commandhistory *history, char *command)
{
	if (history->index > 0 && ft_strcmp(command, history->commands \
		[(history->index - 1) % MAX_HISTORY]) == 0)
		return ;
	if (history->commands[history->index % MAX_HISTORY] != NULL)
	{
		free(history->commands[history->index % MAX_HISTORY]);
	}
	history->commands[history->index % MAX_HISTORY] = ft_strdup(command);
	history->index++;
}

char	*get_from_history(t_commandhistory *history, int index)
{
	if (index < 0 || index >= history->index)
		return (NULL);
	return (history->commands[index % MAX_HISTORY]);
}

char	*cmd_history(t_commandhistory *history)
{
	char	*history_string;
	int		total_length;
	int		i;

	i = 0;
	total_length = 0;
	while (i < history->index)
	{
		total_length += ft_strlen(history->commands[i % MAX_HISTORY]) + 1;
		i++;
	}
	history_string = malloc(total_length + 1);
	history_string[0] = '\0';
	i = 0;
	while (i < history->index)
	{
		ft_strlcat(history_string, history->commands[i % MAX_HISTORY], \
		total_length + 1);
		ft_strlcat(history_string, "\n", total_length + 1);
		i++;
	}
	return (history_string);
}

void	destroy_history(t_commandhistory *history)
{
	int	i;

	i = 0;
	while (i < MAX_HISTORY)
	{
		free(history->commands[i]);
		i++;
	}
	free(history);
}
