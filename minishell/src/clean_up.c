/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:36 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/29 21:32:00 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// free all allocated memory in the pipes array
static void	free_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->pipe_count)
	{
		free(data->pipes[i]);
		data->pipes[i] = NULL;
		i++;
	}
	free(data->pipes);
	data->pipes = NULL;
}

// free allocated memory in the command structure
static void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd_array)
	{
		ft_free_str_arr(cmd->cmd_array);
		cmd->cmd_array = NULL;
	}
	if (cmd->cmd_path)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	free(cmd);
}

// free all allocated memory in the cmds array
static void free_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		free_cmd(cmds[i++]);
	}
	free(cmds);
}

// free allocated memory in the main loop
void	main_loop_free(t_data *data)
{
	if (data->line)
	{
		free(data->line);
		data->line = NULL;
	}
	if (data->line_split)
	{
		ft_free_str_arr(data->line_split);
		data->line_split = NULL;
	}
	if (data->command_split)
	{
		ft_free_str_arr_2d(data->command_split);
		data->command_split = NULL;
	}
	if (data->cmds)
	{
		free_cmds(data->cmds);
		data->cmds = NULL;
	}
	if (data->pipes)
		free_pipes(data);
}

// free all allocated memory
void	clean_up(t_data *data)
{
	if (data)
	{
		if (data->env)
			ft_free_str_arr(data->env);
		if (data->line)
			free(data->line);
		if (data->line_split)
			ft_free_str_arr(data->line_split);
		if (data->command_split)
			ft_free_str_arr_2d(data->command_split);
		if (data->cmd_paths)
			ft_free_str_arr(data->cmd_paths);
		if (data->cmds)
			free_cmds(data->cmds);
		if (data->pipes)
			free_pipes(data);
		if (data->pids_child)
			free(data->pids_child);
	}
}
