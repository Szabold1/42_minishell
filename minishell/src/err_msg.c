/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_msg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszabo <bszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:24:04 by bszabo            #+#    #+#             */
/*   Updated: 2024/03/19 18:53:06 by bszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print error message to stderr with "minishell: " prefix
void	err_msg(char *msg)
{
	ft_printf_fd(2, RED "minishell: " RESET);
	ft_printf_fd(2, "%s\n", msg);
}
