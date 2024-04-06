/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 09:20:23 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/05 18:27:48 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in_out(t_cmd *cmd)
{
	ft_printf_fd(2, "cmd: %s, fd_in: %d, fd_out: %d\n",cmd->cmd_array[0], cmd->fd_in, cmd->fd_out); // for testing
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (err_msg(strerror(errno)), ERROR);
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (err_msg(strerror(errno)), ERROR);
	if (cmd->fd_in > 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out > 1)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
	return (OK);
}

void	child_process(t_data *data, int i)
{
	t_cmd	*cmd;

	cmd = data->cmds[i];
	if (redirect_in_out(cmd) == ERROR)
	{
		clean_up(data);
		exit(1);
	}
	close_pipes(data);
	execve(cmd->cmd_path, cmd->cmd_array, data->env);
	err_msg(strerror(errno));
	clean_up(data);
	exit(1);
}

int	execute_command(t_data *data, int i)
{
	// ft_printf_fd(2, "executing command %d\n", i); // for testing
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (err_msg(strerror(errno)), ERROR);
	if (pid == 0)
		child_process(data, i);
	else
		data->pids_child[i] = pid;
	ft_printf_fd(2, "child pid %d\n", data->pids_child[i]); // for testing
	return (OK);
}

// wait for all child processes to finish
static int	wait_for_children(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_count && data->pids_child[i] > 0)
	{
		ft_printf_fd(2, "waiting for pid %d\n", data->pids_child[i]); // for testing
		waitpid(data->pids_child[i++], NULL, 0);
		ft_printf_fd(2, "waited for pid %d\n", data->pids_child[i - 1]); // for testing
	}
	return (0);
}

// execute the commands
// return ERROR if any of the steps fail, otherwise return OK
int	execute(t_data *data)
{
	int	i;

	i = 0;
	// ft_printf_fd(2, "executing commands\n"); // for testing
	while (i < data->cmd_count)
	{
		if (data->cmds[i]->cmd_path == NULL)
		{
			i++;
			continue;
		}
		if (execute_command(data, i) == ERROR)
			return (ERROR);
		i++;
	}
	// ft_printf_fd(2, "------------ waiting for children ----------------\n"); // for testing
	wait_for_children(data);
	// ft_printf_fd(2, "------------ children finished ----------------\n"); // for testing
	return (OK);
}