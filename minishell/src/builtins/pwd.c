/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:29:27 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 13:47:37 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print the current working directory
void	ms_pwd(t_data *data)
{
	char	**temp;
	char	pwd[PATH_MAX];

	temp = ft_split(data->cmd_line, ' ');
	if (!temp)
		return ;
	if (ft_strcmp(temp[0], "pwd") != 0)
	{
		err_msg(temp[0], "command not found");
		free(temp);
		data->exit_status = 127;
		return ;
	}
	if (getcwd(pwd, PATH_MAX))
		printf("%s\n", pwd);
	else
		perror("Error: getcwd");
	free(temp);
}