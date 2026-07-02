/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:03:27 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 17:03:36 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_all_export(char **env)
{
	int	i;
	int	y;
	int	o;

	i = 0;
	y = 0;
	o = 0;
	export_alpha_sorter(env);
	while (env[y] && env[y][i])
	{
		while (env[y][i])
		{
			printf("%c", env[y][i]);
			if (env[y][i] == '=' && o++ == 0)
				printf("\"");
			i++;
		}
		if (o)
			printf("\"");
		printf("\n");
		o = 0;
		i = 0;
		y++;
	}
}

int	update_env(char ***env_copy, int y, char *env_var)
{
	if (env_var)
	{
		free((*env_copy)[y]);
		(*env_copy)[y] = malloc(sizeof(char) * (strlen(env_var) + 1));
		if (!((*env_copy)[y]))
		{
			ft_putstr_fd("memory allocation failed (update_env)", 2);
			return (0);
		}
		strcpy((*env_copy)[y], env_var);
		return (1);
	}
	free((*env_copy)[y]);
	while ((*env_copy)[y] && (*env_copy)[y + 1])
	{
		(*env_copy)[y] = (*env_copy)[y + 1];
		y++;
	}
	(*env_copy)[y] = NULL;
	return (1);
}

char	**ft_env_copy(char **env, int add)
{
	int		i;
	int		y;
	char	**env_copy;

	env_copy = malloc(sizeof(char *) * (ft_count_envline(env) + add + 1));
	if (!env_copy)
		ft_putstr_fd("memory allocation failed (ft_env_copy)\n", 2);
	if (!env_copy)
		return (NULL);
	y = 0;
	i = 0;
	while (y < ft_count_envline(env))
	{
		while (env[y][i])
			i++;
		env_copy[y] = malloc(sizeof(char) * (i + 1));
		if (!env_copy[y])
			ft_putstr_fd("memory allocation failed (ft_env_copy)\n", 2);
		if (!env_copy[y])
			return (NULL);
		i = 0;
		y++;
	}
	ft_env_copy2(env, env_copy, add);
	return (env_copy);
}

int	add_env_var(char ***env_copy, char *env_var)
{
	int		y;
	char	**new_env;

	y = ft_count_envline(*env_copy);
	new_env = ft_env_copy(*env_copy, 1);
	new_env[y] = malloc(sizeof(char) * (strlen(env_var) + 1));
	if (!(new_env[y]))
	{
		ft_putstr_fd("memory allocation failed (add_env_var)\n", 2);
		return (0);
	}
	strcpy(new_env[y], env_var);
	new_env[y + 1] = NULL;
	free_env(*env_copy);
	*env_copy = new_env;
	return (1);
}
