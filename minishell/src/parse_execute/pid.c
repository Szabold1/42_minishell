/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:19:45 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/24 19:03:45 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add the pid of a child process to the 'pid_array'
void	add_pid(t_data *data, pid_t pid)
{
	int	i;

	i = 0;
	while (i < data->cmd_count && data->pids[i] != -1)
		i++;
	data->pids[i] = pid;
}

// wait for all child processes to finish, and set the exit status if needed
void	wait_for_processes(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->cmd_count && data->pids[i] != -1)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status) && i == data->cmd_count - 1)
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) && i == data->cmd_count - 1)
			data->exit_status = WTERMSIG(status) + 128;
		i++;
	}
}
