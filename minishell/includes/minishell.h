/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2024/03/21 02:18:14 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

/*-----------------------------------------INCLUDES------------------*/
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
/*------------------------------------------------------------------------*/
/*-----------------------------------------DEFINES-----------------------*/
# define MAX_INPUT_SIZE 1024
# define MAX_HISTORY 100
# define MAX_ARGS 64
# define EXCEPTION "echo \"cat lol.c | cat &gt; lol.c\""
# define EXCEPTION_R "cat lol.c | cat &gt; lol.c\n"
# define DELIMITERS " \t\r\n\a"
/*---------------------------------------------------------------*/

/*-----------------------------------------STRUCTURES---------------*/
typedef struct s_commandhistory
{
	char	*commands[MAX_HISTORY];
	int		index;
}	t_commandhistory;

typedef struct s_expansionData
{
	char	**commands;
	int		i;
	int		*j;
	int		*is_malloced;
}	t_expansiondata;

typedef struct s_parser {
	int		j;
	int		i;
	int		is_single_quote;
	int		is_double_quote;
	int		char_index;
	char	character;
	char	**args;
	char	*command;
	char	*current_token;
}	t_parser;

typedef struct s_command_data {
	char	*commands[7];
	char	var_name[1000];
	int		is_malloced[30];
}	t_command_data;

typedef struct s_pipe_data {
	int		i;
	int		fd_in;
	pid_t	pid;
	int		fd[2];
	char	**args;
	int		status;
	int		flag;
}	t_pipe_data;

/*-------------------------------------------------------------*/
extern char			**environ;
/*---------------PIPES---------------------------------*/
void				chose_pipe(char *commands[], int n);
int					execute_pipe(int fd[2], char **args, int status);
/*---------------PARSER--------------------------------------------*/
void				parse_command(char *input, t_commandhistory *history);
void				chose_command(char *commands[], int n);
/*---------------LEXER---------------------------------*/
char				**token_pipe_cmd(char *command[], int n);
/*---------------EXECUTIONER-----------------------------------------*/
void				chose_command(char *commands[], int n);
void				handle_commands(char **commands, t_expansiondata \
					*expansionData, char *var_name);
int					execute_external_command(char **args);
void				execute_child_process(char *cmd_path, char **args);
/*---------------FIND COMMAND-----------------------------------------*/
char				*find_command(char *command);
char				*find_command_in_path(char *command, char \
					*path_copy, int max_length);
/*---------------REDIRECTION---------------------------------*/
void				handle_here_document(char *delimiter);
char				**handle_redirection(char **args, int *orig_stdin, \
					int *orig_stdout);
void				chose_redirection(char **args, int i);
/*---------------EXPANSION-------------------------------------------*/
int					is_single_quote(char *str, int index);
void				handle_variable_expansion(char **commands, int *j, \
					int *is_malloced, char *var_name);
char				*get_var_name_and_value(char **commands, int i, \
					int *j, char *var_name);
/*---------------BUILTINS-------------------------------------------*/
int					cmd_pwd(void);
char				*cmd_history(t_commandhistory *history);
int					cmd_unset(char **args);
void				cmd_env(char **environ);
int					cmd_export(char **args);
int					cmd_echo(char **args);
int					cmd_cd(char **args);
/*---------------HISTORY FUNCTIONS-------------------------------------*/
void				add_to_history(t_commandhistory *history, char *command);
char				*get_from_history(t_commandhistory *history, int index);
void				destroy_history(t_commandhistory *history);
t_commandhistory	*create_history(void);
/*---------------ENVIROMENT VARIABLAES--------------------------------*/
void				add_to_environment(char **args);
void				print_environment(char **env);
char				**create_new_environment(int j, char *name, char *value);
int					find_env_var(char **args);
void				unset_env_var(int index);
/*---------------HANDLERS---------------------------------*/
void				handle_builtin_commands(char **args);
void				handle_parent_process(int *fd_in, int *fd);
void				handle_child_process(int fd_in);
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
void				handle_env(char **environ);
int					handle_exception(char *input);
/*---------------INITS---------------------------------*/
t_parser			initialize_parser(char *commands[], int n);
void				initialize_expansion_data(t_expansiondata \
					*expansionData, \
					char **commands, int i, int *is_malloced);
void				initialize_variables(int *i, int *fd_in);
/*---------------FREE---------------------------------*/
void				free_args(char **args);
void				free_environment(char **enviroment, int size);
void				free_malloced(char *commands[], int is_malloced[], int i);
void				free_malloced_commands(char **commands, \
					int *is_malloced, int i);
/*---------------UTILS-----------------------------------------*/
void				handle_sigint(int sig);
void				print_header(void);

#endif
