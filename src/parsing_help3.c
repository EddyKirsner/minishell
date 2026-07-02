/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_help3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:07:00 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 15:20:13 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	flag_preparse(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == '\\')
				str[i + 1] = -2;
			if (str[i + 1] == '$')
				str[i + 1] = -3;
		}
		i++;
	}
}

void	replace_preparse(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == -2)
			str[i] = '\\';
		if (str[i] == -3)
			str[i] = '$';
		i++;
	}
}

void	delete_bad_chars(char *str, int mode)
{
	int	i;

	i = 0;
	while (str[i] && !mode)
	{
		if (is_in_quote(str, i + 1) || ((str[i] == '\"'
					|| str[i] == '\'') && str[i] == str[i + 1]))
			i += quotes_delete(&str[i]);
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1] == '\\')
				i++;
			str[i] = -1;
		}
		i++;
	}
	remove_chars(str);
}

void	handler_delete_chars(t_all *data)
{
	int	i;
	int	j;

	if (!data->all_cmds[0].args)
		return ;
	i = 0;
	while (i < data->nb_cmds)
	{
		j = 0;
		while (data->all_cmds[i].args[j])
		{
			delete_bad_chars(data->all_cmds[i].args[j], 0);
			replace_preparse(data->all_cmds[i].args[j]);
			j++;
		}
		i++;
	}
}

int	replace_by_expand(char **tab, int i, int exit_code, char **env)
{
	char	*str;

	if (!tab[i])
		return (1);
	str = expand_int(tab[i], exit_code);
	if (!str)
		return (perror("expand_int"), 0);
	str = expand_str(str, env);
	if (!str)
		return (perror("expand_str"), 0);
	if (str == tab[i])
		return (1);
	free(tab[i]);
	tab[i] = str;
	return (1);
}
