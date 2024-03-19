/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:19:30 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/19 18:20:02 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// find next occurrence of 'quote' in 'line' starting at index 'i'
// return index of next 'quote' or index of null terminator
int	find_next_quote(char *line, int i, char quote)
{
	i++;
	while (line[i] && line[i] != quote)
		i++;
	return (i);
}

// check for unclosed quotes, return OK or ERROR
int	check_quotes(t_data *data)
{
	int	i;

	i = 0;
	while (data->line[i])
	{
		if (data->line[i] == S_QUOTE)
		{
			i = find_next_quote(data->line, i, S_QUOTE);
			if (!data->line[i])
				return (ERROR);
		}
		else if (data->line[i] == D_QUOTE)
		{
			i = find_next_quote(data->line, i, D_QUOTE);
			if (!data->line[i])
				return (ERROR);
		}
		i++;
	}
	return (OK);
}