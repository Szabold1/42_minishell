/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:28:50 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/27 14:28:27 by bszabo           ###   ########.fr       */
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
			i++;
		}
		data->cmds[data->cmd_count] = NULL;
	}
	return (OK);
}

// allocate memory for the pids_child array
// return ERROR if malloc fails, OK if successful
static int	alloc_memory_pids_child(t_data *data)
{
	int	i;

	i = 0;
	if (data->pids_child == NULL)
	{
		data->pids_child = malloc(sizeof(pid_t) * data->cmd_count);
		if (!data->pids_child)
			return (ERROR);
		while (i < data->cmd_count)
		{
			data->pids_child[i] = -1;
			i++;
		}
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
			data->pipes[i][0] = -1;
			data->pipes[i][1] = -1;
			i++;
		}
	}
	return (OK);
}

// second part of initialization
// allocate memory for the commands, for the pids_child, and create pipes
int	init_2(t_data *data)
{
	if (alloc_memory_cmds(data) == ERROR)
		return (ERROR);
	if (alloc_memory_pids_child(data) == ERROR)
		return (ERROR);
	if (create_pipes(data) == ERROR)
		return (ERROR);
	return (OK);
}
