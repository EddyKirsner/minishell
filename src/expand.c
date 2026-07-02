/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:55:57 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 17:41:44 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	allocate_full_str(char **new, char **vtab, int nb_env, char **env_copy)
{
	int		i;
	int		full_lenght;
	int		y;

	y = 0;
	full_lenght = count_without(*new);
	*new = NULL;
	i = 0;
	while (i != nb_env)
	{
		y = ft_strstr_env(env_copy, vtab[i]);
		if (y >= 0 && env_copy[y])
		{
			if (!ft_count_and_free0(&full_lenght, env_copy[y]))
				return (ft_fail_memory());
		}
		else
			full_lenght += ft_strlen(vtab[i]);
		i++;
	}
	*new = malloc(sizeof(char) * (full_lenght + 1));
	if (!new)
		return (ft_fail_memory());
	return (1);
}

char	*add_expand(char *str, int *y, char *var_tab, char **env)
{
	int		i;
	char	*expanded;

	i = ft_strstr_env(env, var_tab);
	if (i >= 0)
	{
		expanded = ft_just_env(env[i]);
		if (!expanded)
			return (NULL);
		i = 0;
		while (expanded[i])
		{
			str[*y] = expanded[i];
			i++;
			(*y)++;
		}
		free(expanded);
		return (str);
	}
	return (str);
}

int	inq(char *str, int i)
{
	return (is_in_quote(str, i));
}

char	*write_full_str(char **var_tab, char *str, int nb_env, char **env)
{
	int		i;
	int		y;
	int		x;
	char	*new_str;

	new_str = str;
	if (!allocate_full_str(&new_str, var_tab, nb_env, env) || !new_str)
		return (NULL);
	init_3_int2(&x, &y, &i);
	while (str[i])
	{
		check_incr(str, &i);
		if (str[i] == '$' && inq(str, i) != 39 && (i <= 0 || str[i - 1] != 92))
		{
			if (x < nb_env)
				if (!add_expand(new_str, &y, var_tab[x], env))
					return (ft_free_and_return(new_str));
			increment_2_int(&i, &x);
			while (ft_isalpha(str[i]) || ft_isdigit(str[i]) || (str[i] == '_'))
				i++;
		}
		else
			write_and_increment(new_str, str, &i, &y);
	}
	return (ft_close_and_return(new_str, y));
}

char	*expand_str(char *str, char **env_copy)
{
	int		nb_env;
	int		index;
	char	**var_tab;
	char	*backup_free;

	backup_free = str;
	index = 0;
	nb_env = count_env_var(str);
	if (!nb_env)
		return (str);
	var_tab = malloc(sizeof(char *) * (nb_env + 1));
	if (!var_tab)
		return (ft_malloc_error_expand(var_tab, 1));
	index = allocate_var(str, var_tab);
	if (index == -1)
		return (ft_malloc_error_expand(var_tab, 0));
	write_var(str, var_tab);
	str = write_full_str(var_tab, str, nb_env, env_copy);
	if (!str)
		return (ft_free_expand(var_tab, index, backup_free));
	ft_free_expand(var_tab, index, backup_free);
	return (str);
}
