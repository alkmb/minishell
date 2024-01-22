/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:26 by kmb               #+#    #+#             */
/*   Updated: 2024/01/09 13:57:29 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *command_history[MAX_HISTORY];
int history_index = 0;

CommandHistory* create_history(void)
{
	CommandHistory* history = malloc(sizeof(CommandHistory));
	history->index = 0;
	int i = 0;
	while ( i < MAX_HISTORY)
	{
		history->commands[i] = NULL;
		i++;
	}
	return history;
}

void add_to_history(CommandHistory* history, char *command)
{
	if (history->index > 0 \
	&& strcmp(command, history->commands[(history->index - 1) % MAX_HISTORY]) == 0)
		return;
	if (history->commands[history->index % MAX_HISTORY] != NULL)
	{
		free(history->commands[history->index % MAX_HISTORY]);
	}
	history->commands[history->index % MAX_HISTORY] = strdup(command);
	history->index++;
}

char *get_from_history(CommandHistory* history, int index)
{
	if (index < 0 || index >= history->index)
		return NULL;
	return history->commands[index % MAX_HISTORY];
}

char* cmd_history(CommandHistory* history)
{
	int total_length = 0;
	int i = 0;

	while ( i < history->index)
	{
		total_length += strlen(history->commands[i % MAX_HISTORY]) + 1;
		i++;
	}
	char* history_string = malloc(total_length + 1);

	history_string[0] = '\0';
	i = 0;
	while ( i < history->index)
	{
		strcat(history_string, history->commands[i % MAX_HISTORY]);
		strcat(history_string, "\n");
		i++;
	}
	return history_string;
}

void destroy_history(CommandHistory* history)
{
	int i = 0;
	while ( i < MAX_HISTORY)
	{
		free(history->commands[i]);
		i++;
	}
	free(history);
}
