/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/24 14:06:10 by bszabo           ###   ########.fr       */
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
	return (OK);
}

// split the line by pipes and count the number of commands and pipes
// return ERROR if malloc fails, OK otherwise
static int	split_and_count(t_data *data)
{
	data->line_split = ft_split_quotes(data->line, '|');
	if (!data->line_split)
		return (ERROR);
	data->cmd_count = ft_arrlen(data->line_split);
	data->pipe_count = data->cmd_count - 1;
	return (OK);
}

int	check_line(t_data *data)
{
	if (check_syntax(data) == ERROR)
		return (err_msg("check_syntax failed"), ERROR);
	if (quotes_and_env_var(data) == ERROR)
		return (ERROR);
	if (split_and_count(data) == ERROR)
		return (ERROR);
	printf("line: %s\n", data->line);
	for (int i = 0; i < data->cmd_count; i++)
		printf("line_split[%d]: %s\n", i, data->line_split[i]);
	return (OK);
}
