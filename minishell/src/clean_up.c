/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 21:09:11 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/04 21:48:26 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// clean up everything
void	clean_up(t_data *data)
{
	if (data->cmd_line)
	{
		free(data->cmd_line);
		data->cmd_line = NULL;
	}
	if (data->my_envp)
	{
		ft_free_str_arr(data->my_envp);
		data->my_envp = NULL;
	}
	if (data->paths_arr)
	{
		ft_free_str_arr(data->paths_arr);
		data->paths_arr = NULL;
	}
	free(data);
}