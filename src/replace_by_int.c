/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_by_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:11:04 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/04 19:00:23 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	count_int_var(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if (str[i] == '$' && is_in_quote(str, i) != 39
			&& (i <= 0 || str[i - 1] != 92))
		{
			i++;
			if (str[i] == '?')
				count++;
		}
		else
			i++;
	}
	return (count);
}

static void	add_str_int(char *new_str, char *str_int, int *index)
{
	int	i;

	i = 0;
	while (str_int[i])
	{
		new_str[*index] = str_int[i];
		(*index)++;
		i++;
	}
}

static void	write_int_str(char *new_str, char *str, char *nb_str)
{
	int	y;
	int	x;
	int	i;

	init_3_int2(&y, &x, &i);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if (str[i] == '$' && is_in_quote(str, i) != 39
			&& (i <= 0 || str[i - 1] != 92) && str[i + 1] == '?')
		{
			i++;
			add_str_int(new_str, nb_str, &y);
			i++;
		}
		else
		{
			new_str[y] = str[i];
			y++;
			i++;
		}
	}
	new_str[y] = '\0';
}

char	*expand_int(char *str, int nb)
{
	int		fl;
	int		nb_env;
	char	*new_str;
	char	*nb_str;

	nb_env = count_int_var(str);
	nb_str = ft_itoa(nb);
	if (!nb_str)
	{
		ft_putstr_fd("memory allocation failed (expand_int)\n", 2);
		return (NULL);
	}
	fl = ((nb_env * ft_strlen(nb_str)) + (ft_strlen(str) - (nb_env * 2) + 1));
	new_str = malloc(sizeof(char) * fl);
	if (!new_str)
	{
		free(nb_str);
		ft_putstr_fd("memory allocation failed (expand_int)\n", 2);
		return (NULL);
	}
	write_int_str(new_str, str, nb_str);
	free(nb_str);
	return (new_str);
}
