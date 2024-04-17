/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:14:19 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/16 19:43:50 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the current working directory
void	ms_pwd(t_data *data, int i)
{
	char	*pwd;

	if (data->cmds[i]->cmd_array[1] != NULL)
	{
		data->exit_status = 1;
		return (err_msg2("pwd", "too many arguments"));
	}
	pwd = ms_getenv("PWD", data);
	if (!pwd)
	{
		data->exit_status = 1;
		return (err_msg2("pwd", "PWD not set"));
	}
	printf("%s\n", pwd);
	data->exit_status = 0;
}
