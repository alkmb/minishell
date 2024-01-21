/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/01/21 06:07:13 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_single_quote(char *str, int index)
{
	int i = 0;
	int count = 0;
	while (i < index)
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

void parse_command(char *input, CommandHistory* history)
{
	add_to_history(history, input);

	int i = 0;
	char *commands[7];
	int is_malloced[7] = {0};

	commands[i] = ft_strtok(input, "|");
	while (commands[i] != NULL)
	{
		int j = 0;
		while (commands[i][j] != '\0')
		{
			if (commands[i][j] == '$' && (is_single_quote(commands[i], j)== 0))
			{
				char var_name[20];
				int var_name_len = 0;
				j++;
				while (isalnum(commands[i][j]) || commands[i][j] == '_') {
					var_name[var_name_len++] = commands[i][j++];
				}
				var_name[var_name_len] = '\0';
				char *var_value = getenv(var_name);
				if (var_value != NULL) {
					char *new_command = malloc(strlen(commands[i]) - var_name_len + strlen(var_value) + 1);
					strncpy(new_command, commands[i], j - var_name_len - 1);
					strcpy(new_command + j - var_name_len - 1, var_value);
					strcpy(new_command + j - var_name_len - 1 + strlen(var_value), commands[i] + j);
					if (is_malloced[i]) {
						free(commands[i]);
					}
					commands[i] = new_command;
					is_malloced[i] = 1;
				}
			}
			else
				j++;
		}
		i++;
		commands[i] = ft_strtok(NULL, "|");
	}
	chose_command(commands, i - 1);
	int j = 0;
	while (j <= i)
	{
		if (is_malloced[j])
			free(commands[j]);
		j++;
	}
}

void handle_here_document(char *delimiter)
{
    char *line;
    char *input_buffer = NULL;
    size_t buffer_size = 0;

    printf("heredoc> ");
    while (getline(&line, &buffer_size, stdin) != -1) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, delimiter) == 0) {
            free(line);
            break;
        }

        if (input_buffer == NULL) {
            input_buffer = strdup(line);
        } else {
            size_t current_len = strlen(input_buffer);
            size_t new_len = current_len + strlen(line) + 2;
            input_buffer = realloc(input_buffer, new_len);
            strcat(input_buffer, "\n");
            strcat(input_buffer, line);
        }

        printf("heredoc> ");
    }
    if (input_buffer != NULL) {
        printf("Here document content:\n%s\n", input_buffer);
        free(input_buffer);
    }
}


char **handle_redirection(char **args, int *orig_stdin, int *orig_stdout)
{
	int i = 0;
	*orig_stdin = dup(STDIN_FILENO);
	*orig_stdout = dup(STDOUT_FILENO);

	while (args[i] != NULL) {
		if (strcmp(args[i], ">") == 0 || strcmp(args[i], "<") == 0 || strcmp(args[i], ">>") == 0 || strcmp(args[i], "<<") == 0) {
			int fd;
			if (strcmp(args[i], ">") == 0)
			{
				fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				dup2(fd, STDOUT_FILENO);
			}
			else if (strcmp(args[i], "<") == 0)
			{
				fd = open(args[i+1], O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			else if (strcmp(args[i], ">>") == 0)
			{
				fd = open(args[i+1], O_WRONLY | O_CREAT | O_APPEND, 0644);
				dup2(fd, STDOUT_FILENO);
			}
			else if (strcmp(args[i], "<<") == 0)
			{
				handle_here_document(args[i+1]);
				exit(EXIT_SUCCESS);
			}
			if (fd != -1) {
				close(fd);
			}
			int j = i;
			while (args[j] != NULL)
			{
				args[j] = args[j + 2];
				j++;
			}
		} else
			i++;
	}

	return args;
}

void restore_io(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

void chose_command(char *commands[], int n)
{
	if (n < 0)
		return;
	if (n == 0 && commands[1] != NULL)
	{
		int orig_stdin;
		int orig_stdout;
		char **args;
		args = token_single_cmd(commands, 0);
		args = handle_redirection(args, &orig_stdin, &orig_stdout);
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		restore_io(STDIN_FILENO, STDOUT_FILENO);
		return;
	}
	else
		chose_pipe(commands, n);
}
void	execute_pipe(int fd[2], char **args)
{
			int orig_stdin;
			int orig_stdout;
			args = handle_redirection(args, &orig_stdin, &orig_stdout);
			close(fd[0]);
			close(fd[1]);
			execute_builtin_commandenv(args, environ);
			execute_builtin_command(args);
			restore_io(STDIN_FILENO, STDOUT_FILENO);
			exit(EXIT_SUCCESS);
}

void chose_pipe(char *commands[], int n)
{
	int i = 0;
	pid_t pid;
	int fd[2];
	int fd_in = 0;

	while(i <= n)
	{
		char **args = token_pipe_cmd(commands, i);

		if (strcmp(args[0], "cd") == 0)
			cmd_cd(args);
		else
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				if (fd_in != 0)
				{
					dup2(fd_in, STDIN_FILENO);
					close(fd_in);
				}
				if (i != n)
					dup2(fd[1], STDOUT_FILENO);
				execute_pipe(fd, args);
			}
			else
			{
				wait(NULL);
				if (fd_in != 0)
					close(fd_in);
				fd_in = fd[0];
				close(fd[1]);
			}
		}
		for (int i = 0; args[i] != NULL; i++) {
        	free(args[i]);
    	}
    	free(args);
		i++;
	}
}
