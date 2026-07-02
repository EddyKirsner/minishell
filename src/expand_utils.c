/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:38:59 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 17:21:47 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_env_var(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if ((str[i] == '$' && is_in_quote(str, i) != 39
				&& (i <= 0 || str[i - 1] != 92)))
		{
			i++;
			if (ft_isalpha(str[i]) || ft_isdigit(str[i]) || (str[i] == '_'))
				count++;
			while ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a'
					&& str[i] <= 'z')
				|| (str[i] >= '0' && str[i] <= '9') || (str[i] == '_'))
				i++;
		}
		else
			i++;
	}
	return (count);
}

int	allocate_var(char *str, char **var_tab)
{
	int	i;
	int	index;
	int	count;

	init_3_int(&i, &count, &index);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if ((str[i] == '$' && is_in_quote(str, i) != 39
				&& (i <= 0 || str[i - 1] != 92)))
		{
			increment_2_int(&index, &i);
			while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || (str[i] == '_'))
				increment_2_int(&count, &i);
			var_tab[index] = malloc(sizeof(char) * (count + 1));
			if (!(var_tab[index]))
				return (-1);
			count = 0;
		}
		else
			i++;
	}
	return (index);
}

void	write_var(char *str, char **var_tab)
{
	int	i;
	int	index;
	int	y;

	init_3_int(&i, &y, &index);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		if ((str[i] == '$' && is_in_quote(str, i) != 39
				&& (i <= 0 || str[i - 1] != 92)))
		{
			increment_2_int(&index, &i);
			while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || (str[i] == '_'))
			{
				var_tab[index][y] = str[i];
				increment_2_int(&i, &y);
			}
			var_tab[index][y] = '\0';
			y = 0;
		}
		else
			i++;
	}
}

char	*ft_free_expand(char **var_tab, int index, char *backup_free)
{
	while (index >= 0)
	{
		free(var_tab[index]);
		index--;
	}
	free(var_tab);
	free(backup_free);
	return (NULL);
}
