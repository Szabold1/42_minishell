/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:19:28 by bszabo            #+#    #+#             */
/*   Updated: 2024/05/08 13:18:57 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the path is a directory, return true or false
bool	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		return (true);
	return (false);
}

// check if the command is a builtin, return true or false
bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

// check for valid token after redirection symbol
// return ERROR or OK
int	check_redir_after(char *str_after_redir)
{
	if (!str_after_redir)
		return (err_msg("syntax error"), ERROR);
	if (str_after_redir[0] == '>'
		|| str_after_redir[0] == '<')
		return (err_msg2("syntax error near unexpected token",
				str_after_redir), ERROR);
	return (OK);
}
