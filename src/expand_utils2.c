/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:38:59 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 17:29:22 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*write_false_var(char *var_tab, char *str, int *y)
{
	int	i;

	i = 0;
	while (var_tab[i])
	{
		str[*y] = var_tab[i];
		i++;
		(*y)++;
	}
	return (str);
}

int	count_without(char *str)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if (str[i] == '$' && is_in_quote(str, i)
			!= 39 && (i <= 0 || str[i - 1] != 92))
		{
			i++;
			while ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a'
					&& str[i] <= 'z') || (str[i] >= '0'
					&& str[i] <= '9') || (str[i] == '_'))
				i++;
		}
		else
		{
			i++;
			y++;
		}
	}
	return (y);
}

char	*ft_just_env(char *to_cut)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	y = 0;
	while (to_cut[i] && to_cut[i] != '=')
		i++;
	while (to_cut[i + y])
		y++;
	str = malloc(sizeof(char) * (y + 1));
	if (!str)
		return (NULL);
	y = 0;
	if (to_cut[i])
		i++;
	while (to_cut[i])
	{
		str[y] = to_cut[i];
		y++;
		i++;
	}
	str[y] = '\0';
	return (str);
}

int	ft_count_and_free(char *str)
{
	int		i;
	char	*to_free;

	to_free = ft_just_env(str);
	if (!to_free)
		return (0);
	i = ft_strlen(to_free);
	free(to_free);
	return (i);
}

void	write_and_increment(char *new_str, char *str, int *i, int *y)
{
	new_str[*y] = str[*i];
	increment_2_int(i, y);
}
