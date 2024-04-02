/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:27:38 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/01 19:22:16 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// split the line by pipes and spaces,
// and count the number of commands and pipes
// return ERROR if malloc fails, OK otherwise
static int	split_and_count(t_data *data)
{
	data->line_split = ft_split_quotes(data->line, '|');
	if (!data->line_split)
		return (ERROR);
	data->command_split = ft_split_quotes_2d(data->line_split, ' ');
	data->cmd_count = ft_arrlen(data->line_split);
	data->pipe_count = data->cmd_count - 1;

	printf("line: %s\n", data->line); // for testing
	for (int i = 0; i < data->cmd_count; i++) // for testing
		printf("line_split[%d]: %s\n", i, data->line_split[i]); // for testing
	for (int i = 0; i < data->cmd_count; i++) // for testing
	{
		for (int j = 0; data->command_split[i][j]; j++) // for testing
			printf("command_split[%d][%d]: %s\n", i, j, data->command_split[i][j]); // for testing
	}
	return (OK);
}

int	parse_and_execute(t_data *data)
{
	if (split_and_count(data) == ERROR)
		return (ERROR);
	if (init_2(data) == ERROR)
		return (ERROR);
	// if (handle_commands(data) == ERROR)
	// 	return (ERROR);
	return (OK);
}
