/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 05:05:51 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/10 17:04:53 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// redirect input-output to fd_in, fd_out, or /dev/null
// return ERROR or OK
static int	redirect_redirections(t_data *data, int i)
{
	if (data->cmds[i]->fd_in != -1)
	{
		if (dup2(data->cmds[i]->fd_in, STDIN_FILENO) == -1)
			return (err_msg(strerror(errno)), ERROR);
		close(data->cmds[i]->fd_in);
	}
	if (data->cmds[i]->fd_out != -1)
	{
		if (dup2(data->cmds[i]->fd_out, STDOUT_FILENO) == -1)
			return (err_msg(strerror(errno)), ERROR);
		close(data->cmds[i]->fd_out);
	}
	return (OK);
}

// set redirections for the child process
// return ERROR or OK
static int	set_redirections(t_data *data, int i)
{
	if (i == 0)
	{
		if (dup2(0, STDIN_FILENO) == -1)
			return (err_msg(strerror(errno)), ERROR);
	}
	else
	{
		if (dup2(data->pipes[i - 1][0], STDIN_FILENO) == -1)
			return (err_msg(strerror(errno)), ERROR);
	}
	if (i == data->cmd_count - 1)
	{
		if (dup2(1, STDOUT_FILENO) == -1)
			return (err_msg(strerror(errno)), ERROR);
	}
	else
	{
		if (dup2(data->pipes[i][1], STDOUT_FILENO) == -1)
			return (err_msg(strerror(errno)), ERROR);
	}
	if (redirect_redirections(data, i) == ERROR)
		return (ERROR);
	return (OK);
}

// child process, execute the command if possible, otherwise exit
void	child_process(t_data *data, int i)
{
	t_cmd	*cmd;

	cmd = data->cmds[i];
	if (set_redirections(data, i) == ERROR)
		close_pipes(data), clean_up(data), exit(1);
	close_pipes(data);
	if (cmd->no_infile)
		clean_up(data), exit(1);
	if (is_builtin(cmd->cmd_array[0]))
	{
		execute_builtin(cmd->cmd_array[0], data);
		clean_up(data), exit(data->exit_status);
	}
	if (cmd->cmd_path == NULL)
	{
		err_msg2(cmd->cmd_array[0], "command not found");
		clean_up(data), exit(127);
	}
	execve(cmd->cmd_path, cmd->cmd_array, data->env);
	err_msg(strerror(errno)), clean_up(data), exit(1);
}
