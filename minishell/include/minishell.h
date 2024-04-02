/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:37:09 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/02 09:41:50 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// Define return values
# define OK 0
# define ERROR -1

// Define special characters
# define S_QUOTE '\''
# define D_QUOTE '\"'

// Define ANSI color escape codes
# define NEON "\x1b[38;5;190m"
# define RED "\x1b[31m"
# define RESET "\e[0m"

// Define error messages
# define ARGS_ERROR RED "error:" RESET " minishell cannot take any arguments\n"

// Define the prompt
# define PROMPT NEON "minishell$ " RESET

// Define the command structure
typedef struct s_cmd
{
	char	**cmd_array; // {"ls", "-l", NULL}
	char	*cmd_path; // "/bin/ls"
}	t_cmd;

// Define the main data structure
typedef struct s_data
{
	char	**env; // copy of the environment
	char	*line; // "ls -l | sort | grep a > output.txt"
	char	**line_split; // split by "|" {"ls -l", "sort", "grep a > output.txt"}
	char	***command_split; // split by " " {{ls, -l, NULL}, {sort, NULL}, {grep, a, >, output.txt, NULL}}
	char	**cmd_paths; // array of paths to commands
	t_cmd	**cmds; // array of commands
	int		**pipes; // array of pipes to connect commands
	pid_t	*pids_child; // array of child process ids
	int		cmd_count; // 3 (number of commands in the line)
	int		pipe_count; // 2 (number of pipes in the line)
	int		exit_status;
}	t_data;

// Function prototypes
char	*ms_getenv(char *name, t_data *data);
int		init(t_data *data, char *env[]);

/* *********************************************************** Input checking */
// File: src/input_check/check_line.c
int		check_line(t_data *data);
// File: src/input_check/env_variables.c
int		replace_env_variables_in_quotes(t_data *data, int q_start, int q_end);
int		replace_env_variable(t_data *data, int i);
// File: src/input_check/exit_status.c
int		replace_exit_status(t_data *data, int i, int *q_end);
// File: src/input_check/quotes.c
int		quotes_envvar_redir(t_data *data);
// File: src/input_check/redirections_space.c
int		separate_redirections(t_data *data, int i);

/* ************************************************************* Line parsing */
// File: src/line_parsing/parse_line.c
int		parse_line(t_data *data);
// File: src/line_parsing/init_2.c
int		init_2(t_data *data);

/* ********************************************** Clean up and error handling */
// File: src/clean_up.c
void	main_loop_free(t_data *data);
void	clean_up(t_data *data);
// File: src/err_msg.c
void	err_msg(char *msg);

# endif