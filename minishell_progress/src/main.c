/* ************************************************************************** */
/*			    */
/*					:::      ::::::::   */
/*   main.c					 :+:      :+:    :+:   */
/*			    +:+ +:+		 +:+     */
/*   By: kmb <kmb@student.42.fr>					+#+  +:+       +#+		*/
/*			+#+#+#+#+#+   +#+		   */
/*   Created: 2023/12/20 23:23:40 by kmb			   #+#    #+#			 */
/*   Updated: 2024/01/05 18:09:48 by kmb			  ###   ########.fr       */
/*			    */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **split_args(char *args) {
	if (args == NULL) {
		fprintf(stderr, "Error: args is null\n");
		return NULL;
	}

	char **result = malloc(MAX_ARGS * sizeof(char *));
	if (result == NULL) {
		fprintf(stderr, "Error: malloc failed\n");
		return NULL;
	}

	char *saveptr;
	char *token = strtok_r(args, " ", &saveptr);
	int i = 0;

	while (token != NULL) {
		result[i] = token;
		token = strtok_r(NULL, " ", &saveptr);
		i++;
	}
	result[i] = NULL;  // Null-terminate the array
	return result;
}

char **split_string(char *str, char *delimiters)
{
	int i = 0;
	int arg_count = 0;
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *arg = NULL;

	if (args == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	arg = str;
	i = 0;
	while ( str[i] != '\0')
	{
		if (ft_strchr(delimiters, str[i]) != NULL)
		{
			str[i] = '\0';
			args[arg_count] = arg;
			arg_count++;
			arg = &str[i + 1];
		}
		i++;
	}
	if (arg != &str[i])
	{
		args[arg_count] = arg;
		arg_count++;
	}

	args[arg_count] = NULL;

	return args;
}

void execute_builtin_command(char **args) {
	if (strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
			fprintf(stderr, "cd: expected argument\n");
		else
		{
			if (chdir(args[1]) != 0)
				perror("cd");
		}
	}
	else
	{
		for (int i = 0; commands[i].name != NULL; i++) {
			if (strcmp(args[0], commands[i].name) == 0) {
				commands[i].func(args);
				return;
			}
		}
	}
}

void execute_builtin_commandenv(char **args, char **environ) {
	for (int i = 0; commandsenv[i].name != NULL; i++) {
		if (strcmp(args[0], commandsenv[i].name) == 0) {
			commandsenv[i].func(environ);
			return;
		}
	}
}

void execute_command(char *commands[], int n)
{
	if (n < 0) {
		// Base case: no more commands to execute
		return;
	}

    if (n == 0) {
        // Only one command, execute it without creating a pipe
        char *args[MAX_ARGS];
        int i = 0;

        args[i] = strtok(commands[n], " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        execute_builtin_commandenv(args, environ);
        execute_builtin_command(args);
        return;
    }

	int fd[2];
	pid_t pid;

	// Create a pipe
	if (pipe(fd) == -1) {
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}

	if ((pid = fork()) == -1) {
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		// Child process: execute the current command
		close(fd[0]);
		if (n > 0) {
			// If this is not the last command, redirect output to the pipe
			dup2(fd[1], STDOUT_FILENO);
		}
		close(fd[1]);

		char *args[MAX_ARGS];
		int i = 0;

		args[i] = strtok(commands[n], " ");
		while (args[i] != NULL) {
			i++;
			args[i] = strtok(NULL, " ");
		}

		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		exit(EXIT_FAILURE);  // Exit if execvp fails
	} else {
		// Parent process: execute the next command
		close(fd[1]);
		if (n > 0) {
			// If there are more commands, redirect input from the pipe
			dup2(fd[0], STDIN_FILENO);
		}
		close(fd[0]);

		wait(NULL);  // Wait for the child process to finish

		execute_command(commands, n - 1);  // Recursive call outside of the forked process
	}
}
Command commands[] = {
	{"echo", cmd_echo},
	{"pwd", cmd_pwd},
	{"unset", cmd_unset},
	{"cd", cmd_cd},
	{"export", cmd_export},
	{NULL, NULL}  // End marker
};

Commandenv commandsenv[] = {
	{"env", cmd_env},
	{NULL, NULL}  // End marker
};

int main() {
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
			free(input);  // Free the input buffer
			break;
		}

		// Remove the newline character at the end of the input
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
