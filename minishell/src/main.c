/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 21:19:39 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 13:46:16 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtins(t_data *data)
{
	if (ft_strncmp(data->cmd_line, "cd", 2) == 0)
		ms_cd(data);
	else if (ft_strcmp(data->cmd_line, "env") == 0)
		ms_env(data->my_envp);
	else if (ft_strncmp(data->cmd_line, "pwd", 3) == 0)
		ms_pwd(data);
	else if (ft_strcmp(data->cmd_line, "exit") == 0)
		ms_exit(data);
	return (0);
}

void	handle_cmd_line(t_data *data)
{
	// add the 'cmd_line' to the history
	add_history(data->cmd_line);
	// parse the 'cmd_line'
	// parse_cmd_line(data);
	// execute the command
	// execute_cmd(data);
	// free the 'cmd_line'
	free(data->cmd_line);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	if (argc != 1 || argv[1] || !envp)
		return (ft_printf_fd(2, ARGS_ERROR), EXIT_FAILURE);
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	if (init(data, envp) == -1)
		return (clean_up(data), EXIT_FAILURE);
	while (1)
	{
		data->cmd_line = readline(PROMPT);
		if (!data->cmd_line)
			break ;
		handle_builtins(data);
		handle_cmd_line(data);
	}
	clean_up(data);
	return (0);
}
