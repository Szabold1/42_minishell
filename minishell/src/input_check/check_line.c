/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/20 12:31:59 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if the line has a syntax error
// return ERROR if it does, OK otherwise
static int	check_syntax(t_data *data)
{
	int		len;

	len = ft_strlen(data->line);
	if (data->line[0] == '|' || data->line[len - 1] == '|'
		|| data->line[0] == ';' || data->line[len - 1] == ';'
		|| data->line[0] == '\\' || data->line[len - 1] == '\\'
		|| data->line[0] == '>' || data->line[len - 1] == '>'
		|| data->line[0] == '<' || data->line[len - 1] == '<')
	{
		data->exit_status = 2;
		return (err_msg("syntax error"), ERROR);
	}
	if (check_quotes(data) == ERROR)
	{
		data->exit_status = 2;
		return (err_msg("quote error"), ERROR);
	}
	return (OK);
}

// remove leading and trailing spaces from each command in the line
// example: {" ls -l ", " sort "} -> {"ls -l", "sort"}
// return ERROR if malloc fails, OK otherwise
static int	trim_line_split(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (data->line_split[i])
	{
		temp = ft_strtrim(data->line_split[i], " ");
		if (!temp)
			return (ERROR);
		free(data->line_split[i]);
		data->line_split[i] = temp;
		i++;
	}
	return (OK);
}

// split the line by pipes and count the number of commands and pipes
// return ERROR if malloc fails, OK otherwise
static int	split_and_count(t_data *data)
{
	data->line_split = ft_split_quotes(data->line, '|');
	if (!data->line_split)
		return (ERROR);
	if (trim_line_split(data) == ERROR)
		return (ERROR);
	data->cmd_count = ft_arrlen(data->line_split);
	data->pipe_count = data->cmd_count - 1;
	return (OK);
}

int	check_line(t_data *data)
{
	if (check_syntax(data) == ERROR)
		return (ERROR);
	if (handle_env_variables(data) == ERROR)
		return (ERROR);
	if (split_and_count(data) == ERROR)
		return (ERROR);
	return (OK);
}
