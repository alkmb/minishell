/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:26 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 00:36:35 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//FUNCTION TO CREATE THE HISTORY
t_commandhistory	*create_history(void)
{
	t_commandhistory	*history;
	int					i;

	i = 0;
	//ALLOCATING MEMORY FOR THE HISTORY
	history = malloc((sizeof(t_commandhistory) - 1));
	history->index = 0;
	//ALLOCATING MEMORY FOR THE COMMANDS
	while (i < MAX_HISTORY - 1)
	{
		history->commands[i] = NULL;
		i++;
	}
	return (history);
}

//FUNCTION TO ADD TO THE HISTORY
void	add_to_history(t_commandhistory *history, char *command)
{
	//CHECKING IF THE COMMAND IS THE SAME AS THE PREVIOUS ONE
	if (history->index > 0 && strcmp(command, history->commands \
		[(history->index - 1) % MAX_HISTORY]) == 0)
		return ;
	//FREEING THE MEMORY OF THE COMMAND
	if (history->commands[history->index % MAX_HISTORY] != NULL)
	{
		free(history->commands[history->index % MAX_HISTORY]);
	}
	//ALLOCATING MEMORY FOR THE COMMAND
	history->commands[history->index % MAX_HISTORY] = strdup(command);
	history->index++;
}

//FUNCTION TO GET FROM THE HISTORY
char	*get_from_history(t_commandhistory *history, int index)
{
	//CHECKING IF THE INDEX IS VALID
	if (index < 0 || index >= history->index)
		return (NULL);
	//RETURNING THE COMMAND
	return (history->commands[index % MAX_HISTORY]);
}

char	*cmd_history(t_commandhistory *history)
{
	char	*history_string;
	int		total_length;
	int		i;

	i = 0;
	total_length = 0;
	//CALCULATING THE TOTAL LENGTH OF THE HISTORY
	while (i < history->index)
	{
		total_length += strlen(history->commands[i % MAX_HISTORY]) + 1;
		i++;
	}
	//ALLOCATING MEMORY FOR THE HISTORY
	history_string = malloc(total_length + 1);
	history_string[0] = '\0';
	i = 0;
	//COPYING THE HISTORY INTO THE STRING
	while (i < history->index)
	{
		strcat(history_string, history->commands[i % MAX_HISTORY]);
		strcat(history_string, "\n");
		i++;
	}
	return (history_string);
}

//FUNCTION TO DESTROY THE HISTORY
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
