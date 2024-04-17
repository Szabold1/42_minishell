/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:53:15 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 08:19:19 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set input redirection
// example: "grep a < input.txt"
// return ERROR or OK
static int	set_input(t_data *data, int i, int j)
{
	if (data->cmds[i]->no_infile)
		return (OK);
	if (!data->command_split[i][j + 1])
		return (err_msg("no input file after '<'"), ERROR);
	reset_fd(data->cmds[i]->fd_in);
	data->cmds[i]->fd_in = open(data->command_split[i][j + 1], O_RDONLY);
	if (data->cmds[i]->fd_in == -1)
	{
		data->cmds[i]->fd_in = open("/dev/null", O_RDONLY);
		if (data->cmds[i]->fd_in == -1)
			return (err_msg("failed to open /dev/null"), ERROR);
		data->exit_status = 1;
		if (data->cmds[i]->no_infile == false)
		{
			data->cmds[i]->no_infile = true;
			err_msg2(data->command_split[i][j + 1], strerror(errno));
		}
	}
	return (OK);
}

// loop for here document
static void	heredoc_loop(t_data *data, int i, int j)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, data->command_split[i][j + 1]) == 0)
		{
			free(line);
			break ;
		}
		ft_printf_fd(data->cmds[i]->fd_in, "%s\n", line);
		free(line);
	}
}

// set here document redirection
// example: "grep a << EOF"
// return ERROR or OK
static int	set_heredoc(t_data *data, int i, int j)
{
	if (!data->command_split[i][j + 1])
		return (err_msg("no delimiter after '<<'"), ERROR);
	reset_fd(data->cmds[i]->fd_in);
	data->cmds[i]->fd_in = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->cmds[i]->fd_in == -1)
		return (err_msg("failed to open /tmp/heredoc"), ERROR);
	heredoc_loop(data, i, j);
	close(data->cmds[i]->fd_in);
	data->cmds[i]->fd_in = open("/tmp/heredoc", O_RDONLY);
	if (data->cmds[i]->fd_in == -1)
		return (err_msg("failed to open /tmp/heredoc"), ERROR);
	return (OK);
}

// handle input redirection ('<' or '<<')
// return ERROR or OK
int	handle_input(t_data *data, int i, int j)
{
	if (ft_strcmp(data->command_split[i][j], "<") == 0)
	{
		if (set_input(data, i, j) == ERROR)
			return (ERROR);
	}
	else if (ft_strcmp(data->command_split[i][j], "<<") == 0)
	{
		if (set_heredoc(data, i, j) == ERROR)
			return (ERROR);
	}
	return (OK);
}
