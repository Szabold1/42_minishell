/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 07:41:24 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/08 08:10:29 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// close file descriptor if it is not -1, and set it to -1
void	reset_fd(int fd)
{
	if (fd != -1)
	{
		close(fd);
		fd = -1;
	}
}

// free allocated memory in the main loop and close the file descriptors
void	clean_up_loop(t_data *data)
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
		free_pipes(data);
}
