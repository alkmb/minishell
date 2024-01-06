/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 09:50:47 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

Command commands[] = {
	{"echo", cmd_echo},
	{"pwd", cmd_pwd},
	{"unset", cmd_unset},
	{"cd", cmd_cd},
	{"export", cmd_export},
	{NULL, NULL}
};

Commandenv commandsenv[] = {
	{"env", cmd_env},
	{NULL, NULL}
};

int main(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;
	char *commands[7];

	while (1) {
		printf("$ ");
		read = getline(&input, &len, stdin);
		if (read == -1) {
			if (feof(stdin)) {
				printf("End of input\n");
			} else {
				perror("Error reading input");
			}
			free(input);
			break;
		}
		if (input[read - 1] == '\n') {
			input[read - 1] = '\0';
		}
		int i = 0;
		commands[i] = strtok(input, "|");
		while (commands[i] != NULL) {
			i++;
			commands[i] = strtok(NULL, "|");
		}
		for (int j = 0; j < i; j++) {
			commands[j] = strtok(commands[j], " ");
		}
		execute_command(commands, i - 1);
		free(input);
		input = NULL;
	}
	return 0;
}
