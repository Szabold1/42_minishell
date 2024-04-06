/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 06:53:15 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/06 09:34:51 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// set input redirection
// example: "grep a < input.txt"
// return ERROR or OK
static int	set_input(t_data *data, int i, int j)
{
	if (!data->command_split[i][j + 1])
		return (err_msg("no input file after '<'"), ERROR);
	data->cmds[i]->fd_in = open(data->command_split[i][j + 1], O_RDONLY);
	if (data->cmds[i]->fd_in == -1)
	{
		data->cmds[i]->fd_in = open("/dev/null", O_RDONLY);
		if (data->cmds[i]->fd_in == -1)
			return (err_msg("failed to open /dev/null"), ERROR);
		err_msg2(data->command_split[i][j + 1], strerror(errno));
		data->no_infile = true;
	}
	return (OK);
}

// set here document redirection
// example: "grep a << EOF"
// return ERROR or OK
static int	set_heredoc(t_data *data, int i, int j)
{
	char	*line;

	if (!data->command_split[i][j + 1])
		return (err_msg("no delimiter after '<<'"), ERROR);
	data->cmds[i]->fd_in = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (data->cmds[i]->fd_in == -1)
		return (err_msg("failed to open /tmp/heredoc"), ERROR);
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
