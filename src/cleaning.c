/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:39:53 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 16:06:07 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_array_null_end(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	close_both_fds(t_cmd *cmd)
{
	if (cmd->fd_in >= 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = -1;
	}
	if (cmd->fd_out >= 0)
	{
		close(cmd->fd_out);
		cmd->fd_out = -1;
	}
}

void	free_structs(t_all *data, int limit)
{
	int	i;

	i = 0;
	while (i < limit && i < data->nb_cmds)
	{
		if (data->all_cmds[i].args)
			free_array_null_end(data->all_cmds[i].args);
		free(data->all_cmds[i].cut_line);
		close_both_fds(&data->all_cmds[i]);
		i++;
	}
	free(data->all_cmds);
	data->all_cmds = NULL;
}

void	clean_all(t_all *data)
{
	if (data->full_line)
	{
		free(data->full_line);
		data->full_line = NULL;
	}
	if (data->all_cmds)
		free_structs(data, data->nb_cmds);
	if (!access("here_doc", F_OK))
		unlink("here_doc");
}

void	end_clean(t_all *data, char *error, int exit_code)
{
	if (error)
		perror(error);
	clean_all(data);
	free_array_null_end(data->envp);
	rl_clear_history();
	exit(exit_code);
}
