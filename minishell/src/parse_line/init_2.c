/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:28:50 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/10 17:27:11 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// allocate memory for the commands array and its members
// return ERROR if malloc fails, OK if successful
static int	alloc_memory_cmds(t_data *data)
{
	int	i;

	i = 0;
	if (data->cmds == NULL)
	{
		data->cmds = malloc(sizeof(t_cmd *) * (data->cmd_count + 1));
		if (!data->cmds)
			return (ERROR);
		while (i < data->cmd_count)
		{
			data->cmds[i] = (t_cmd *)malloc(sizeof(t_cmd));
			if (!data->cmds[i])
				return (ERROR);
			data->cmds[i]->cmd_array = NULL;
			data->cmds[i]->cmd_path = NULL;
			data->cmds[i]->fd_in = -1;
			data->cmds[i]->fd_out = -1;
			data->cmds[i]->no_infile_name = NULL;
			data->cmds[i]->no_infile = false;
			data->cmds[i]->pid = -1;
			i++;
		}
		data->cmds[data->cmd_count] = NULL;
	}
	return (OK);
}

// create pipes for the commands
// return ERROR if pipe fails, OK if successful
static int	create_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipes == NULL)
	{
		data->pipes = (int **)malloc(sizeof(int *) * data->pipe_count);
		if (!data->pipes)
			return (ERROR);
		while (i < data->pipe_count)
		{
			data->pipes[i] = (int *)malloc(sizeof(int) * 2);
			if (!data->pipes[i])
				return (ERROR);
			if (pipe(data->pipes[i]) == -1)
				return (ERROR);
			i++;
		}
	}
	for (int i = 0; i < data->pipe_count; i++) // for testing
	{
		printf("pipe %d[0]: %d\n", i, data->pipes[i][0]); // for testing
		printf("pipe %d[1]: %d\n", i, data->pipes[i][1]); // for testing
	}
	return (OK);
}

// second part of initialization
// allocate memory for the commands, for the pids_child, and create pipes
int	init_2(t_data *data)
{
	if (alloc_memory_cmds(data) == ERROR)
		return (ERROR);
	if (create_pipes(data) == ERROR)
		return (ERROR);
	return (OK);
}
