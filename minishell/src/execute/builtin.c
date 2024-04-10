/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:38:29 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/08 11:46:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// execute the builtin command
void	execute_builtin(char *cmd, t_data *data)
{
	if (ft_strcmp(cmd, "echo") == 0)
		ms_echo(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		ms_cd(data);
	else if (ft_strcmp(cmd, "pwd") == 0)
		ms_pwd(data);
	else if (ft_strcmp(cmd, "export") == 0)
		ms_export(data);
	else if (ft_strcmp(cmd, "unset") == 0)
		ms_unset(data);
	else if (ft_strcmp(cmd, "env") == 0)
		ms_env(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		ms_exit(data);
}
