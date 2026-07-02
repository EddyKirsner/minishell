/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:14:11 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 16:03:47 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_builtins_parent(char **args, t_all *data)
{
	if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args[1], &data->envp), 1);
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(&data->envp, args), 1);
	if (!ft_strcmp(args[0], "export") && args[1])
		return (ft_export(&data->envp, args), 1);
	return (0);
}

int	handle_builtins_child(char **args, t_all *data)
{
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args), 1);
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(), 1);
	if (!ft_strcmp(args[0], "env"))
		return (ft_print_env(data->envp), 1);
	if (!ft_strcmp(args[0], "export"))
		return (print_all_export(data->envp), 1);
	return (0);
}

int	launch_process(t_all *data, int i, int *cmd_count)
{
	pid_t	process;

	if (handle_builtins_parent(data->all_cmds[i].args, data))
		return (1);
	else
	{
		process = fork();
		if (process == -1)
			return (perror("fork"), 0);
		if (!process)
			work_child(data, i);
		*cmd_count += 1;
	}
	return (1);
}

int	is_regular_file(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	if (!S_ISREG(statbuf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is not a regular file\n", 2);
		return (free(path), 0);
	}
	return (1);
}
