/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:09:35 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 16:16:36 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_update_pwd(char ***env_copy, char *old_pwd, char *path)
{
	char	*to_send;

	to_send = ft_strjoin("OLDPWD=", old_pwd);
	if (!to_send)
		return (0);
	if (!ft_update_pwd2(env_copy, to_send))
	{
		free(to_send);
		return (0);
	}
	free(to_send);
	to_send = ft_strjoin("PWD=", path);
	if (!to_send)
		return (0);
	if (!ft_update_pwd2(env_copy, to_send))
	{
		free(to_send);
		return (0);
	}
	free(to_send);
	return (1);
}

int	ft_update_pwd2(char ***env_copy, char *env_var)
{
	int	y;

	y = ft_strstr_env(*env_copy, env_var);
	if (y >= 0)
	{
		if (strchr(env_var, '='))
		{
			if (!update_env(env_copy, y, env_var))
				return (0);
		}
	}
	else
		add_env_var(env_copy, env_var);
	return (1);
}
