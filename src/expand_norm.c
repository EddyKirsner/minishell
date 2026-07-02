/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:37:35 by ekirsner          #+#    #+#             */
/*   Updated: 2025/03/28 17:39:24 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_3_int(int *i, int *y, int *index)
{
	*i = 0;
	*y = 0;
	*index = -1;
}

void	init_3_int2(int *i, int *y, int *x)
{
	*i = 0;
	*y = 0;
	*x = 0;
}

void	increment_2_int(int *i, int *y)
{
	(*i) = (*i) + 1;
	(*y) = (*y) + 1;
}

void	check_incr(char *str, int *i)
{
	if (!str || !i)
		return ;
	if (str[*i] == '\\')
		(*i) = (*i) + 1;
}

char	*ft_malloc_error_expand(char **var_tab, int ok)
{
	if (ok)
		ft_putstr_fd("memory allocation failed (expand_str)\n", 2);
	else
		free(var_tab);
	return (NULL);
}
