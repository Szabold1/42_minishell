/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:13:23 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 20:04:38 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit minishell
void	ms_exit(t_data *data, int i)
{
	if (data->cmds[i]->cmd_array[1] != NULL)
	{
		err_msg2("exit", "too many arguments");
		data->exit_status = 1;
	}
	if (i == 0 && data->cmd_count == 1)
	{
		clean_up(data);
		printf("exit\n");
		exit(data->exit_status);
	}
}
