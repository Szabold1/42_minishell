/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 07:41:24 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/06 07:41:49 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_up_loop_1(t_data *data)
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
		clean_up_cmds(data->cmds);
		data->cmds = NULL;
	}
	if (data->pipes)
		clean_up_pipes(data);
}

static void	clean_up_loop_2(t_data *data)
{
	if (data->pids_child)
	{
		free(data->pids_child);
		data->pids_child = NULL;
	}
}

// free allocated memory in the main loop and close the file descriptors
void	clean_up_loop(t_data *data)
{
	clean_up_loop_1(data);
	clean_up_loop_2(data);
}