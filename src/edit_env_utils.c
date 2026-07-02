/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:39:22 by ekirsner          #+#    #+#             */
/*   Updated: 2025/03/26 18:32:14 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_env(char **env)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (env[y])
	{
		while (env[y][i])
		{
			printf("%c", env[y][i]);
			i++;
		}
		printf("\n");
		i = 0;
		y++;
	}
}

void	print_all_export2(char **env)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (env[y] && env[y][i])
	{
		while (env[y][i])
		{
			printf("%c", env[y][i]);
			i++;
		}
		i = 0;
		printf("\n");
		y++;
	}
}

void	ft_env_copy2(char **env, char **envcopy, int add)
{
	int	i;
	int	y;

	y = 0;
	i = 0;
	while (env[y] && env[y][i])
	{
		while (env[y][i] && env[y])
		{
			envcopy[y][i] = env[y][i];
			i++;
		}
		envcopy[y][i] = '\0';
		i = 0;
		y++;
	}
	envcopy[y] = NULL;
	if (add)
		envcopy[y + 1] = NULL;
}
