/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:36 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/25 18:33:39 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

// free allocated memory in the command structure
static void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd_array)
		ft_free_str_arr(cmd->cmd_array);
	if (cmd->cmd_path)
		free(cmd->cmd_path);
	free(cmd);
}

// free all allocated memory in the cmds array
static void free_cmds(t_cmd **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		free_cmd(cmds[i++]);
	free(cmds);
}

// free all allocated memory in the pipes array
static void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
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
			free_pipes(data->pipes);
		if (data->pids_child)
			free(data->pids_child);
	}
}
