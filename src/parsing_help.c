/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:41:42 by ktaouach          #+#    #+#             */
/*   Updated: 2025/03/28 18:08:48 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	seek_if_char(char *str)
{
	int	i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i])
		return (1);
	return (0);
}

int	check_if_operator(char *str, int *j)
{
	int	i;

	i = *j;
	if (!is_in_quote(str, i) && (str[i] == '|' || str[i] == '<'
			|| str[i] == '>'))
	{
		if ((str[i] == '<' || str[i] == '>') && str[i + 1] == str[i])
		{
			i++;
			*j = i;
		}
		if (str[i + 1] && str[i + 1] != '|' && str[i + 1] != '<'
			&& str[i + 1] != '>' && seek_if_char(&str[i + 1])
			&& (!i || str[i - 1] != '\\'))
			return (1);
	}
	return (0);
}

int	is_in_quote(char *str, int i)
{
	int		j;
	char	inquote;

	j = 0;
	inquote = 0;
	while (str[j] && j < i)
	{
		if (!j || (j && str[j - 1] != '\\'))
		{
			if (str[j] == inquote)
				inquote = 0;
			else if (!inquote && (str[j] == '\"' || str[j] == '\''))
				inquote = str[j];
		}
		j++;
	}
	if (inquote == str[j] && (!j || (j && str[j - 1] != '\\')))
		return (0);
	return (inquote);
}

int	count_commands(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		count += check_if_operator(str, &i);
		i++;
	}
	if (is_in_quote(str, i))
	{
		str[0] = 0;
		return (ft_putstr_fd("minishell: syntax error\n", 2), 0);
	}
	return (count + 1);
}

//will check bad operators
int	syntax_check(t_all *data)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	while (i < data->nb_cmds)
	{
		while (data->all_cmds[i].cut_line[j])
		{
			c = data->all_cmds[i].cut_line[j];
			if ((c == '|' || c == '>' || c == '<') && (!j
					|| data->all_cmds[i].cut_line[j - 1] != '\\')
				&& !is_in_quote(data->all_cmds[i].cut_line, j))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}
