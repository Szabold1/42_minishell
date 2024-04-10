/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 13:42:31 by bszabo            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/19 19:51:42 by seckhard         ###   ########.fr       */
=======
/*   Updated: 2024/04/08 07:07:44 by bszabo           ###   ########.fr       */
>>>>>>> main
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
<<<<<<< HEAD
		sig_cases(data, INTERACTIVE);
=======
		clean_up_loop(data);
		// handle_signals();
>>>>>>> main
		data->line = readline(PROMPT);
		// sig_cases(data, NONINTERACTIVE);
		if (g_signal == CTRLC && g_signal--)
			data->exit_status = 130;
		if (!data->line)
		{
			printf("exit\n");
			return (clean_up(data), OK);
		}
		if (ft_strlen(data->line) > 0)
		{
			if (ft_strcmp(data->line, "exit") == 0) // for testing
				return (clean_up(data), data->exit_status); // for testing
			add_history(data->line);
			if (check_line(data) == ERROR)
				continue;
			if (parse_line(data) == ERROR)
				continue;
			if (execute(data) == ERROR)
				continue;
		}
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
