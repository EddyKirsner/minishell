/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:39:14 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 17:04:06 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count_envline(char **env)
{
	int	i;

	i = 0;
	while (env[i] && env[i][0])
		i++;
	return (i);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	export_alpha_sorter(char **env)
{
	int		i;
	int		y;
	char	*temp;

	i = 0;
	y = 1;
	while (env[i] && env[y])
	{
		if (strcmp(env[i], env[y]) > 0)
		{
			temp = env[y];
			env[y] = env[i];
			env[i] = temp;
			i = 0;
			y = 1;
		}
		i++;
		y++;
	}
}

char	*just_var_name(char *little)
{
	int		i;
	char	*var_name;

	i = 0;
	while (little[i] && little[i] != '=')
		i++;
	if (little[i] == '=')
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	var_name[i] = '\0';
	i--;
	while (i >= 0)
	{
		var_name[i] = little[i];
		i--;
	}
	return (var_name);
}

int	ft_strstr_env(char **env, char *little)
{
	int	i;
	int	y;
	int	x;

	init_3_int2(&x, &i, &y);
	while (env[y] && env[y][0])
	{
		while (env[y][x] != '=' && env[y][x])
		x++;
		i = ft_strncmp(env[y], little, x);
		if (i == '=' || i == 0)
			return (y);
		x = 0;
		y++;
	}
	return (-1);
}
