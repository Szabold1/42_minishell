/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seckhard <seckhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:13:23 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/18 22:27:51 by seckhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Check if string is a valid integer
static bool	is_valid_int(const char *str)
{
	if (!str || *str == '\0')
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

// bool	is_valid_int(char *str)
// {
// 	if (*str == '-' || *str == '+' || ft_isdigit(*str) == 1)
// 		str++;
// 	else
// 		return (false);
// 	while (*str)
// 	{
// 		if (ft_isdigit(*str) == 0)
// 			return (false);
// 		str++;
// 	}
// 	return (true);
// }

static void	strip_quotes2(char *str)
{
	char	*current;
	char	*result;

	current = str;
	result = str;
	while (*current)
	{
		if ((*current == '"' || *current == '\'') && *(current + 1) == *current)
			current++;
		else
		{
			*result = *current;
			result++;
		}
		current++;
	}
	*result = '\0';
}

static void strip_quotes(char *str)
{
    if (str && *str == '"' && str[ft_strlen(str) - 1] == '"')
    {
        ft_memmove(str, str + 1, ft_strlen(str) - 1);
        str[ft_strlen(str) - 2] = '\0';
    }
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
		strip_quotes2(data->cmds[i]->cmd_array[1]);
		strip_quotes(data->cmds[i]->cmd_array[1]);
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

void ms_exit(t_data *data, int i)
{
	printf("exit\n");
	handle_exit_logic(data, i);
}

// void	ms_exit(t_data *data, int i)
// {
// 	if (data->cmds[i]->cmd_array[2] != NULL)
// 	{
// 		printf("exit\n");
// 		err_msg2("exit", "too many arguments");
// 		data->exit_status = 1;
// 		return ;
// 	}
// 	if (data->cmds[i]->cmd_array[1] != NULL)
// 	{
// 		strip_quotes2(data->cmds[i]->cmd_array[1]);
// 		strip_quotes(data->cmds[i]->cmd_array[1]);
// 		if (is_valid_int(data->cmds[i]->cmd_array[1]))
// 		{
// 			data->exit_status = ft_atoi(data->cmds[i]->cmd_array[1]);
// 			printf("exit\n");
// 			clean_up(data);
// 			exit(data->exit_status);
// 		}
// 		printf("exit\n");
// 		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", \
// 		 data->cmds[i]->cmd_array[1]);
// 		data->exit_status = 2;
// 		clean_up(data);
// 		exit(data->exit_status);
// 	}
// 	printf("exit\n");
// 	clean_up(data);
// 	exit(data->exit_status);
// }
