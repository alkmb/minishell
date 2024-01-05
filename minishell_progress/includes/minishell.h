/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2024/01/05 19:41:16 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

extern char	**environ;

# define MAX_INPUT_SIZE 1024
# define MAX_HISTORY 100
# define MAX_ARGS 64
# define READ_END 0
# define WRITE_END 1
# define FILE1 1
# define CMD1 2
# define CMD2 3
# define FILE2 4
# define DELIMITERS " \t\r\n\a"

typedef struct CommandHistory
{
	char *commands[MAX_HISTORY];
	int index;
} CommandHistory;

typedef struct {
	char *name;
	void (*func)(char **);
} Commandenv;

typedef struct {
	char *name;
	void (*func)(char **);
} Command;

extern Command commands[];
extern Commandenv commandsenv[];
/*---------------UTILS------------------------------------------------------------*/
char			**split_string(char *str, char *delimiters);
/*---------------BUILTINS----------------------------------------------------------*/
void cmd_echo(char **args);
void cmd_pwd();
void cmd_unset(char **args);
void cmd_cd(char **args);
void cmd_env(char **environ);
void cmd_export(char **args);
void execute_command(char *commands[], int i);

/*---------------HISTORY-----------------------------------------------------------*/
void			add_to_history(CommandHistory* history, char *command);
char			*get_from_history(CommandHistory* history, int index);
CommandHistory*	create_history(void);
void destroy_history(CommandHistory* history);
/*---------------PIPES---------------------------------------------------------*/
void	execute_first_command(int *fd, char **argv, char **envp);
void	execute_second_command(int *fd, char **argv, char **envp);
void	execute_mid_command(int *fd_old, int *fd_new, char *argv, char **envp);
void	execute_last_command(int *fd_old, int argc, char **argv, char **envp);
void	chose_command(int *fd_old, int argc, char **argv, char **envp);
void	exec_cmd(char *cmd, char **envp);
void	free_array(char **array);
char	*get_path(char *cmd, char **envp);
char	*get_envp(char *name, char **envp);

#endif
