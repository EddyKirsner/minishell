/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:15:00 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 16:02:21 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	autodup(int *to_inject_in, int to_replace)
{
	if (*to_inject_in == -2)
		autodup_heredoc();
	if (*to_inject_in < 0)
		return ;
	if (dup2(*to_inject_in, to_replace) >= 0)
	{
		close(*to_inject_in);
		*to_inject_in = -1;
	}
	else
		perror("autodup");
}

static
	char	*make_path(char *path, char *arg)
{
	char	*full_path;
	char	*res;

	full_path = ft_strjoin(path, "/");
	if (!full_path)
		return (NULL);
	res = ft_strjoin(full_path, arg);
	return (free(full_path), res);
}

static
	void	access_issue(char *arg, t_all *data, char **paths)
{
	if (access(arg, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		if (ft_strchr(arg, '/'))
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		free_array_null_end(paths);
		end_clean(data, NULL, 127);
	}
	if (access(arg, X_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_array_null_end(paths);
		end_clean(data, NULL, 126);
	}
}

char	*try_paths(char **paths, char *arg, t_all *data)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = make_path(paths[i], arg);
		if (!full_path)
			return (perror("try_paths"), NULL);
		if (!access(full_path, F_OK | X_OK))
			return (full_path);
		free(full_path);
		i++;
	}
	access_issue(arg, data, paths);
	return (ft_strdup(arg));
}

char	**empty_env(void)
{
	char	**res;

	res = malloc((sizeof(char *)));
	if (!res)
		return (NULL);
	res[0] = NULL;
	return (res);
}
