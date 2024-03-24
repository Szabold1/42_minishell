/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:19:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/24 14:50:57 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find next occurrence of 'quote' in 'data->line' starting at index 'i'
// replace environment variables with their values if in double quotes
// return index of next 'quote' or index of null terminator
static int	find_next_quote(t_data *data, int i, char quote)
{
	int		start;
	bool	has_env_var;
	char	*line;

	start = i;
	has_env_var = false;
	line = data->line;
	i++;
	while (line[i] && line[i] != quote)
	{
		if (line[i] == '$' && quote == D_QUOTE)
			has_env_var = true;
		i++;
	}
	if (has_env_var)
		i = replace_env_variables_in_quotes(data, start, i);
	return (i);
}

// check if the line has unclosed quotes,
// and replace environment variables where necessary
// return ERROR, or OK if successful
int	quotes_and_env_var(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == S_QUOTE)
		{
			i = find_next_quote(data, i, S_QUOTE);
			if (!data->line[i])
				return (err_msg("unclosed single quote"), ERROR);
		}
		else if (data->line[i] == D_QUOTE)
		{
			i = find_next_quote(data, i, D_QUOTE);
			if (!data->line[i])
				return (err_msg("unclosed double quote"), ERROR);
		}
		else if (data->line[i] == '$' && data->line[i + 1])
			i = replace_env_variable(data, i);
		i++;
	}
	return (OK);
}
