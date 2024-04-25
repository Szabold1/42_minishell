/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:37:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/25 07:05:35 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if there are two pipe symbols after each other
// if there are return ERROR, otherwise return OK
static int	check_pipe_symbols(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i++] == '|')
		{
			while (data->line[i] == ' ')
				i++;
			if (data->line[i] == '|')
			{
				data->exit_status = 2;
				return (err_msg("syntax error"), ERROR);
			}
		}
	}
	return (OK);
}

// check if the line has a syntax error
// return ERROR if it does, OK otherwise
static int	check_syntax(t_data *data)
{
	int	len;

	len = ft_strlen(data->line);
	if (data->line[0] == '|' || data->line[len - 1] == '|'
		|| data->line[0] == ';' || data->line[len - 1] == ';'
		|| data->line[0] == '\\' || data->line[len - 1] == '\\'
		|| data->line[0] == '>' || data->line[len - 1] == '>'
		|| data->line[len - 1] == '<')
	{
		data->exit_status = 2;
		return (err_msg("syntax error"), ERROR);
	}
	if (check_pipe_symbols(data) == ERROR)
		return (ERROR);
	return (OK);
}

// check line beginnings and endings, check quotes, replace environment
// variables, replace '$?', and separate redirection symbols
int	check_line(t_data *data)
{
	if (check_syntax(data) == ERROR)
		return (ERROR);
	if (quotes_envvar_redir(data) == ERROR)
		return (ERROR);
	return (OK);
}
