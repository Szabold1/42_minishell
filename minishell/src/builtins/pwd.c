/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:14:19 by bszabo            #+#    #+#             */
/*   Updated: 2024/04/13 10:41:59 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pwd(t_data *data)
{
	char	*pwd;

	pwd = ms_getenv("PWD", data);
	if (!pwd)
	{
		data->exit_status = 1;
		return (err_msg("pwd: PWD not set"));
	}
	printf("%s\n", pwd);
	data->exit_status = 0;
}
