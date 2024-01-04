/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2023/12/21 02:45:43 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_unset(char **args)
{
	if (args[1] != NULL)
		unsetenv(args[1]);
	else
		fprintf(stderr, "Usage: unset variable_name\n");
}

void cmd_cd(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
			perror("chdir failed");
		else
			fprintf(stderr, "Usage: cd directory_path\n");
	}
}

void cmd_env(char **environ)
{
	char *env_var = *environ;
	while (env_var != NULL)
	{
		ft_printf("%s\n", env_var);
		env_var = *(environ++);
	}
}

void cmd_export(char **args)
{
	if (args[1] != NULL && args[2] != NULL)
		setenv(args[1], args[2], 1);
	else
		fprintf(stderr, "Usage: export variable_name value\n");
}

void cmd_external(char **args)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args);
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("Fork failed");
	else
		wait(NULL);
}

void	free_split(char **split)
{
	char	**original_split;

	original_split = split;
	while (*split != NULL)
	{
		free(*split);
		split++;
	}
	free(original_split);
}

void chose_command(int *fd_old, int argc, char **argv, char **envp)
{
	int fd_new[2];
	char *args[MAX_ARGS];
	int i, j;

	// Split argv into separate arguments
	i = 0;
	j = 0;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "|", i) == 0)
		{
			args[j] = NULL;
			pipe(fd_new);
			if (fork() == 0)
			{
				execute_mid_command(fd_old, fd_new, args, envp);
			}
			close(fd_old[0]);
			close(fd_old[1]);
			fd_old[0] = fd_new[0];
			fd_old[1] = fd_new[1];
			j = 0;
		}
		else
		{
			args[j] = argv[i];
			j++;
		}
		i++;
	}
	args[j] = NULL;

	// Execute the last command
	if (fork() == 0)
	{
		execute_last_command(fd_old, argc, args, envp);
	}
	close(fd_old[0]);
	close(fd_old[1]);
}

void	exec_cmd(char *cmd, char **envp)
{
	char	*path;
	char	**all_cmd;
	char	**original_cmd;

	all_cmd = ft_split(cmd, ' ');
	original_cmd = all_cmd;
	path = get_path(cmd, envp);
	if (execve(path, all_cmd, envp) == -1)
	{
		ft_putstr_fd ("Command not found.\n", 2);
		exit(EXIT_FAILURE);
	}
	free_split(original_cmd);
	free(path);
}

char	*get_envp(char *n_envp, char **envp)
{
	char	*envp_path;
	char	*result;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		envp_path = ft_substr(envp[i], 0, j);
		if (ft_strncmp(envp_path, n_envp, j) == 0)
		{
			result = envp[i] + j + 1;
			free(envp_path);
			return (result);
		}
		free(envp_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*cmd_pth;
	char	*path_part;
	char	**all_path;
	char	**all_cmd;

	i = 0;
	all_path = ft_split(get_envp("PATH", envp), ':');
	all_cmd = ft_split(cmd, ' ');
	if (all_path == NULL || all_cmd == NULL)
		return (NULL);
	while (all_path[i])
	{
		path_part = ft_strjoin(all_path[i], "/");
		cmd_pth = ft_strjoin(path_part, all_cmd[0]);
		free(path_part);
		if (access(cmd_pth, F_OK | X_OK) == 0)
			return (cmd_pth);
		free(cmd_pth);
		i++;
	}
	free_split(all_path);
	free_split(all_cmd);
	return (cmd);
}
void	execute_first_command(int *fd, char **argv, char **envp)
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	exec_cmd(argv[0], envp);
	perror("Error executing first command");
	exit(EXIT_FAILURE);
}

void execute_mid_command(int *fd_old, int *fd_new, char **argv, char **envp)
{
	dup2(fd_old[0], 0);
	dup2(fd_new[1], 1);
	close(fd_old[0]);
	close(fd_old[1]);
	close(fd_new[0]);
	close(fd_new[1]);
	execve(argv[0], argv, envp);
	perror("Error executing mid command");
	exit(EXIT_FAILURE);
}

void execute_last_command(int *fd_old, int argc, char **argv, char **envp)
{
	if (dup2(fd_old[0], 0) == -1)
	{
		perror("Error duplicating file descriptor to stdin");
		exit(EXIT_FAILURE);
	}
	close(fd_old[0]);
	close(fd_old[1]);
	exec_cmd(argv[argc - 1], envp);

	perror("Error executing command");
	exit(EXIT_FAILURE);
}

void	parent_proces(int *fd_old, char **argv, char **envp, int argc)
{
	pid_t	pid;

	if (pipe(fd_old) == -1)
	{
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		execute_first_command(fd_old, argv, envp);
	else
	{
		wait(NULL);
		close(fd_old[1]);
		chose_command(fd_old, argc, argv, envp);
	}
}
void execute_pipeline(char ***argv, int n, char **envp)
{
	int i;
	int fd[2];

	// Execute the first command
	pipe(fd);
	if (fork() == 0)
	{
		execute_first_command(fd, argv[0], envp);
	}

	// Execute the middle commands
	for (i = 1; i < n - 1; i++)
	{
		int fd_old[2] = {fd[0], fd[1]};
		pipe(fd);
		if (fork() == 0)
		{
			execute_mid_command(fd_old, fd, argv[i], envp);
		}
		close(fd_old[0]);
		close(fd_old[1]);
	}

	// Execute the last command
	if (fork() == 0)
	{
		execute_last_command(fd, n, argv[n - 1], envp);
	}
	close(fd[0]);
	close(fd[1]);

	// Wait for all commands to finish
	for (i = 0; i < n; i++)
	{
		wait(NULL);
	}
}

int exec_command(int argc, char **argv, char **envp)
{
	char ***commands;
	int i, j, n;

	// Allocate memory for commands
	commands = malloc(sizeof(char **) * MAX_ARGS);
	for (i = 0; i < MAX_ARGS; i++)
	{
		commands[i] = malloc(sizeof(char *) * MAX_ARGS);
	}

	// Split argv into separate commands
	i = 0;
	j = 0;
	n = 0;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "|", i) == 0)
		{
			commands[n][j] = NULL;
			n++;
			j = 0;
		}
		else
		{
			commands[n][j] = argv[i];
			j++;
		}
		i++;
	}
	commands[n][j] = NULL;
	n++;

	// Execute the pipeline
	execute_pipeline(commands, n, envp);

	// Free memory
	for (i = 0; i < MAX_ARGS; i++)
	{
		free(commands[i]);
	}
	free(commands);

	return 0;
}

