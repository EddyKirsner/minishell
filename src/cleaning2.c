/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:36:32 by ktaouach          #+#    #+#             */
/*   Updated: 2025/03/31 14:40:26 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	clean_all_fds(t_all *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		if (data->all_cmds[i].fd_in >= 0)
			close(data->all_cmds[i].fd_in);
		if (data->all_cmds[i].fd_out >= 0)
			close(data->all_cmds[i].fd_out);
		data->all_cmds[i].fd_in = -1;
		data->all_cmds[i].fd_out = -1;
		i++;
	}
}
