/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:23:58 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 16:16:27 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//token is char * 10, +5 if double arrow
//| is 1240
//< is 600
//> is 620
//<< is 605
//>> is 625
static
	int	place_cut_line(t_all *data, int i, int j)
{
	static int	k = 0;

	if (k && !j)
		k = 0;
	if (i && (data->full_line[i - 1] == data->full_line[i])
		&& (data->full_line[i] == '>' || data->full_line[i] == '<'))
	{
		i--;
		data->all_cmds[k].token = data->full_line[i] * 10 + 5;
	}
	else
		data->all_cmds[k].token = data->full_line[i] * 10;
	data->all_cmds[k].cut_line = malloc((sizeof(char)) * (i - j + 1));
	if (!data->all_cmds[k].cut_line)
		return (free_structs(data, k), 0);
	ft_strlcpy(data->all_cmds[k].cut_line, &data->full_line[j], i - j + 1);
	k++;
	return (1);
}

//i for str iter, j for keeping last placement, k for array iter
static
	int	cut_lines(t_all *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (1)
	{
		if (!data->full_line[i] || check_if_operator(data->full_line, &i))
		{
			if (!place_cut_line(data, i, j))
				return (0);
			if (!data->full_line[i])
				break ;
			j = i + 1;
		}
		i++;
	}
	return (1);
}

static
	int	split_cutline(t_all *data)
{
	int		i;
	char	**array;

	i = 0;
	while (i < data->nb_cmds)
	{
		array = ft_split_quotes(data->all_cmds[i].cut_line);
		if (!array)
			return (0);
		data->all_cmds[i].args = array;
		i++;
	}
	return (1);
}

static
	int	expand_all_lines(t_all *data)
{
	int		i;
	int		excode;
	char	**env;

	i = 0;
	env = data->envp;
	excode = data->last_exitcode;
	while (i < data->nb_cmds)
	{
		if (!replace_by_expand(&data->all_cmds[i].cut_line, 0, excode, env))
			return (0);
		i++;
	}
	return (1);
}

int	handle_parsing(t_all *data)
{
	flag_preparse(data->full_line);
	data->nb_cmds = count_commands(data->full_line);
	if (!data->nb_cmds)
		return (1);
	data->all_cmds = malloc((sizeof(t_cmd)) * (data->nb_cmds));
	if (!data->all_cmds)
		return (0);
	fill_cmds_null(data);
	if (!cut_lines(data))
		return (0);
	if (!syntax_check(data))
		return (ft_putstr_fd("minishell: syntax error\n", 2), 1);
	if (!expand_all_lines(data))
		return (0);
	if (!split_cutline(data))
		return (0);
	handler_delete_chars(data);
	return (1);
}
