/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:26:27 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/05 13:43:37 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_msg(char *cmd, char *msg)
{
	ft_printf_fd(2, "minishell: ");
	if (cmd)
		ft_printf_fd(2, "%s: ", cmd);
	if (msg)
		ft_printf_fd(2, "%s\n", msg);
	else
		ft_printf_fd(2, "error\n");
}