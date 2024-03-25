/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:42:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/25 18:31:48 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main loop for minishell
// handle signals, read line, add it to history, parse, execute, and free line
// return ERROR if any of the steps fail
static int	main_loop(t_data *data)
{
	while (1)
	{
		// handle_signals();
		data->line = readline(PROMPT);
		if (!data->line)
			return (clean_up(data), ERROR);
		if (ft_strlen(data->line) > 0)
		{
			add_history(data->line);
			if (check_line(data) == ERROR)
				return (err_msg("check_line failed"), ERROR);
			if (parse_line(data) == ERROR)
				return (err_msg("parse_line failed"), ERROR);
			// if (exec_line(data) == ERROR)
			// 	return (ERROR);
		}
		main_loop_free(data);
	}
	return (OK);
}

// 1. check arguments
// 2. initialize data
// 3. main loop
int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	if (argc != 1 || argv[1] || !env)
		return (ft_printf_fd(2, ARGS_ERROR), ERROR);
	if (init(&data, env) == ERROR)
		return (clean_up(&data), ERROR);
	if (main_loop(&data) == ERROR)
		return (err_msg("main_loop failed"), clean_up(&data), ERROR);
}
