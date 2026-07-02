/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:42:57 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 16:31:28 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	fill_cmds_null(t_all *data)
{
	int	i;

	i = 0;
	while (i < data->nb_cmds)
	{
		data->all_cmds[i].args = NULL;
		data->all_cmds[i].cut_line = NULL;
		data->all_cmds[i].fd_in = -1;
		data->all_cmds[i].fd_out = -1;
		data->all_cmds[i].x = 1;
		data->all_cmds[i].excode = data->last_exitcode;
		data->all_cmds[i].envp_ptr = &data->envp;
		i++;
	}
	if (i)
		i--;
	data->all_cmds[i].x = 0;
}

//add any other whitespace here
//current: space, newline, carriage return, vert. tab, hori. tab
int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	init_struct_null(t_all *data)
{
	data->full_line = NULL;
	data->nb_cmds = 0;
	data->all_cmds = NULL;
	data->last_exitcode = 0;
	data->envp = NULL;
}

int	quotes_delete(char *str)
{
	int	i;

	i = 1;
	while (is_in_quote(str, i))
		i++;
	str[0] = -1;
	str[i] = -1;
	return (i);
}

void	remove_chars(char *str)
{
	int		i;
	size_t	siz;

	i = 0;
	while (str[i])
	{
		if (str[i] == -1)
		{
			siz = ft_strlen(&str[i + 1]) + 1;
			ft_strlcpy(&str[i], &str[i + 1], siz);
		}
		else
			i++;
	}
}
