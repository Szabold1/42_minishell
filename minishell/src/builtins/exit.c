/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:13:23 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/20 18:09:27 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if string is a valid integer
static bool	is_valid_int(char *str)
{
	char		*llong_max_str;
	const char	*p;

	llong_max_str = "9223372036854775807";
	p = str;
	if (!str || *str == '\0')
		return (false);
	if (*p == '-' || *p == '+')
		p++;
	while (*p)
	{
		if (*p < '0' || *p > '9')
			return (false);
		p++;
	}
	if (ft_strlen(str) > ft_strlen(llong_max_str) || \
		(ft_strlen(str) == ft_strlen(llong_max_str) \
			&& ft_strcmp(str, llong_max_str) > 0))
		return (false);
	return (true);
}

static void	handle_exit_logic(t_data *data, int i)
{
	if (data->cmds[i]->cmd_array[2] != NULL)
	{
		err_msg2("exit", "too many arguments");
		data->exit_status = 1;
		return ;
	}
	if (data->cmds[i]->cmd_array[1] != NULL)
	{
		remove_quotes(data->cmds[i]->cmd_array[1]);
		if (is_valid_int(data->cmds[i]->cmd_array[1]))
		{
			data->exit_status = ft_atoi(data->cmds[i]->cmd_array[1]);
			clean_up(data);
			exit(data->exit_status);
		}
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", \
			data->cmds[i]->cmd_array[1]);
		data->exit_status = 2;
		clean_up(data);
		exit(data->exit_status);
	}
	clean_up(data);
	exit(data->exit_status);
}

void	ms_exit(t_data *data, int i)
{
	printf("exit\n");
	handle_exit_logic(data, i);
}
