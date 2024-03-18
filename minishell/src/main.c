/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:42:31 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/18 22:39:16 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// main loop for minishell
// handle signals, read line, add it to history, parse, execute, and free line
// return ERROR if any of the steps fail
int	main_loop(t_data *data)
{
	while (1)
	{
		sig_cases(data, INTERACTIVE);
		data->line = readline(PROMPT);
		// sig_cases(data, NONINTERACTIVE);
		if (!data->line)
		{
			printf("exit\n");
			return (clean_up(data), OK);
		}
		if (ft_strlen(data->line) > 0)
		{
			add_history(data->line);
			// if (parse_line(data) == ERROR)
			// 	return (ERROR);
			// if (exec_line(data) == ERROR)
			// 	return (ERROR);
		}
		free(data->line);
	}
	return (OK);
}

// 1. check arguments
// 2. initialize data
// 3. main loop
// 4. clean up and exit
int	main(int argc, char *argv[], char *env[])
{
	t_data	data;

	if (argc != 1 || argv[1] || !env)
		return (ft_printf_fd(2, ARGS_ERROR), ERROR);
	if (init(&data, env) == ERROR)
		return (clean_up(&data), ERROR);
	if (main_loop(&data) == ERROR)
		return (clean_up(&data), ERROR);
}
