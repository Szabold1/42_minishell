/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:20:01 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 13:45:23 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>


// Define ANSI color escape codes
# define ANSI_NEON "\x1b[38;5;190m"
# define ANSI_RED "\x1b[31m"
# define ANSI_RESET "\e[0m"

# define PROMPT ANSI_NEON "minishell " ANSI_RED "> " ANSI_RESET
# define ARGS_ERROR "Error: minishell cannot take any arguments\n"

// structure for data related to the command
typedef struct s_cmd
{
	char	**cmd_arr;
	char	*path;
}	t_cmd;

typedef struct s_data
{
	int		exit_status;
	char	*cmd_line;
	char	**my_envp;
	char	**paths_arr;
	t_cmd	*cmds;
}	t_data;

/* builtins ***************************************** ms stands for minishell */

void	ms_cd(t_data *data);
// File: cd.c

int		ms_setenv(char *var_name, char *value, t_data *data);
char	*ms_getenv(char *var_name, t_data *data);
void	ms_env(char *envp[]);
// File: env.c

void	ms_exit(t_data *data);
// File: exit.c

void	ms_pwd(t_data *data);
// File: pwd.c

/* ************************************************************************** */

void	clean_up(t_data *data);
// File: clean_up.c

void	err_msg(char *cmd, char *msg);
// File: errors.c

int		init(t_data *data, char *envp[]);
// File: init.c


#endif