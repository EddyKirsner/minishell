/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 23:42:50 by ktaouach          #+#    #+#             */
/*   Updated: 2025/03/16 23:55:37 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_pipe(t_all *data, int new_i, int i)
{
	int	tube[2];

	if (pipe(tube))
		perror("set_pipe");
	data->all_cmds[new_i + 1].fd_in = tube[0];
	if (data->all_cmds[i].fd_out >= 0)
	{
		close(tube[1]);
		return ;
	}
	data->all_cmds[i].fd_out = tube[1];
}
