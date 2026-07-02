/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:09:35 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 17:53:38 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
		perror("getcwd");
}

int	ft_cd(char *path, char ***env_copy)
{
	char	*old_pwd;
	int		i;

	old_pwd = getcwd(NULL, 0);
	if (!path || !*path)
		path = getenv("HOME");
	if (!path)
	{
		printf("HOME not set\n");
		return (0);
	}
	if (chdir(path) < 0)
	{
		perror("cd");
		return (0);
	}
	setenv("OLDPWD", old_pwd, 1);
	path = getcwd(NULL, 0);
	setenv("PWD", path, 1);
	i = ft_update_pwd(env_copy, old_pwd, path);
	free(old_pwd);
	free(path);
	if (!i)
		return (0);
	return (1);
}

int	ft_export(char ***env_copy, char **env_var)
{
	int	y;
	int	i;

	i = 1;
	while (env_var[i])
	{
		y = ft_strstr_env(*env_copy, env_var[i]);
		if (y >= 0)
		{
			if (strchr(env_var[i], '='))
			{
				if (!update_env(env_copy, y, env_var[i]))
					return (0);
			}
		}
		else if (y == -1)
			add_env_var(env_copy, env_var[i]);
		i++;
	}
	return (1);
}

int	ft_unset(char ***env, char **arg)
{
	int	i;
	int	y;

	y = 1;
	while (arg[y])
	{
		i = ft_strstr_env(*env, arg[y]);
		if (i >= 0)
		{
			if (!update_env(env, i, NULL))
				return (0);
		}
		else if (i == -1)
			ft_putstr_fd("unset argument doesn't exist\n", 2);
		y++;
	}
	return (1);
}

int	ft_echo(char **arg)
{
	int	i;
	int	option;

	i = 1;
	option = 0;
	if (!arg[1])
		return (write(1, "\n", 1));
	if (ft_strncmp("-n", arg[1], 2) == 0)
		option = 1;
	i = i + option;
	while (arg[i] && arg[i][0])
	{
		ft_putstr_fd(arg[i], 1);
		if ((arg[i + 1] && arg[i + 1][0]))
			write(1, " ", 1);
		if ((!arg[i + 1] || !arg[i + 1][0]))
			if (!option)
				write(1, "\n", 1);
		i++;
	}
	return (0);
}
