/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:26 by kmb               #+#    #+#             */
/*   Updated: 2024/01/07 17:37:28 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// CASI TODO FUNCIONA RARO PORQUE NOSE DE LISTAS XD


// ESTO ES UNA ESTRUCTURA QUE CONTIENE EL HISTORIAL
char *command_history[MAX_HISTORY];
int history_index = 0;

// CREAMOS EL HISTORIAL
CommandHistory* create_history(void)
{
	// ALLOCAMOS MEMORIA PARA EL HISTORIAL
	CommandHistory* history = malloc(sizeof(CommandHistory));
	// INICIALIZAMOS EL INDEX A 0
	history->index = 0;
	int i = 0;
	// INICIALIZAMOS EL ARRAY DE COMANDOS A NULL
	while ( i < MAX_HISTORY)
	{
		history->commands[i] = NULL;
		i++;
	}
	return history;
}

void add_to_history(CommandHistory* history, char *command)
{
	// SI EL COMANDO ES IGUAL AL ANTERIOR NO LO AÑADIMOS(funcina mal)
	if (history->index > 0 \
	&& ft_strcmp(command, history->commands[(history->index - 1) % MAX_HISTORY]) == 0)
		return;
	// SI EL COMANDO ES IGUAL A "HISTORY" NO LO AÑADIMOS(funcina mal tambien)
	if (history->commands[history->index % MAX_HISTORY] != NULL)
		free(history->commands[history->index % MAX_HISTORY]);
	// AÑADIMOS EL COMANDO AL HISTORIAL
	history->commands[history->index % MAX_HISTORY] = strdup(command);
	history->index++;
}

char* cmd_history(CommandHistory* history)
{
	int total_length = 0;
	int i = 0;

	// CALCULAMOS LA LONGITUD TOTAL DE LA STRING DEL HISTORIAL
	while ( i < history->index)
	{
		total_length += ft_strlen(history->commands[i % MAX_HISTORY]) + 1;
		i++;
	}
	// ALLOCAMOS MEMORIA PARA LA STRING DEL HISTORIAL
	char* history_string = malloc(total_length + 1);

	history_string[0] = '\0';
	i = 0;
	// CONCATENAMOS TODOS LOS COMANDOS DEL HISTORIAL EN UNA STRING
	while ( i < history->index)
	{
		ft_strlcat(history_string, history->commands[i % MAX_HISTORY], \
		ft_strlen(history_string) + 1);
		ft_strlcat(history_string, "\n", ft_strlen(history_string) + 2);
		i++;
	}
	// RETORNAMOS LA STRING DEL HISTORIAL
	return history_string;
}

// DESTRUYE EL HISTORIAL LIBERABDOLO
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
