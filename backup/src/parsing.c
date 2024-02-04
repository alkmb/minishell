/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/02/04 03:59:23 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parse_command(char *input, t_commandhistory *history)
{
	int		i;
	int		j;
	char	*commands[7];
	char	var_name[20];
	int		var_name_len;
	char	*var_value;
	char	*new_command;
	int		is_malloced[7] = {0};

	i = 0;
	var_name_len = 0;
	add_to_history(history, input);
	commands[i] = ft_strtok(input, "|");
	while (commands[i] != NULL)
	{
		j = 0;
		while (commands[i][j] != '\0')
		{
			if (commands[i][j] == '$' \
				&& (is_single_quote(commands[i], j) == 0))
			{
				j++;
				while (ft_isalnum(commands[i][j]) || commands[i][j] == '_')
					var_name[var_name_len++] = commands[i][j++];
				var_name[var_name_len] = '\0';
				var_value = getenv(var_name);
				if (var_value != NULL)
				{
					new_command = malloc(ft_strlen(commands[i]) \
						- var_name_len + ft_strlen(var_value) + 1);
					ft_strlcpy(new_command, commands[i], j - var_name_len);
					ft_strlcpy(new_command + j - var_name_len - 1, var_value, \
						ft_strlen(var_value) + 1);
					ft_strlcpy(new_command + j - var_name_len - 1
						+ ft_strlen(var_value), commands[i] + j, \
						ft_strlen(commands[i] + j) + 1);
					if (is_malloced[i])
						free(commands[i]);
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
	j = 0;
	while (j < i)
	{
		if (is_malloced[j])
			free(commands[j]);
		j++;
	}
}

void	chose_command(char *commands[], int n)
{
	if (n < 0)
		return ;
	else
		chose_pipe(commands, n);
}

void	execute_pipe(int fd[2], char **args)
{
	int	orig_stdin;
	int	orig_stdout;
	int	exit_status;

	exit_status = 0;
	args = handle_redirection(args, &orig_stdin, &orig_stdout);
	close(fd[0]);
	close(fd[1]);
	execute_builtin_commandenv(args, environ);
	execute_builtin_command(args, &exit_status);
	restore_io(STDIN_FILENO, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	chose_pipe(char *commands[], int n)
{
	int		i;
	int		j;
	int		fd_in;
	pid_t	pid;
	int		fd[2];
	char	**args;

	fd_in = 0;
	i = 0;
	j = 0;
	while (i <= n)
	{
		args = token_pipe_cmd(commands, i);
		if (ft_strcmp(args[0], "cd") == 0)
			cmd_cd(args);
		else if (ft_strcmp(args[0], "export") == 0)
			cmd_export(args);
		else if (ft_strcmp(args[0], "unset") == 0)
			cmd_unset(args);
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
		j = 0;
		while (args[j] != NULL)
			free(args[j++]);
		free(args);
		i++;
	}
}
