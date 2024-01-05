
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
	&& strcmp(command, history->commands[(history->index - 1) % MAX_HISTORY]) == 0) {
		return;
	}
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
	// Calculate the total length of the history string
	int total_length = 0;
	for (int i = 0; i < history->index; i++) {
		total_length += strlen(history->commands[i % MAX_HISTORY]) + 1; // +1 for the newline
	}

	// Allocate memory for the history string
	char* history_string = malloc(total_length + 1); // +1 for the null terminator
	history_string[0] = '\0'; // Start with an empty string

	// Concatenate all commands into the history string
	for (int i = 0; i < history->index; i++) {
		strcat(history_string, history->commands[i % MAX_HISTORY]);
		strcat(history_string, "\n");
	}

	return history_string;

}

void destroy_history(CommandHistory* history) {
	for (int i = 0; i < MAX_HISTORY; i++) {
		free(history->commands[i]);
	}
	free(history);
}
