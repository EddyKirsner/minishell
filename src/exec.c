/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:16:52 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 18:13:51 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_paths(char **env)
{
	int		i;
	char	**result;
	char	*path_var;

	if (!env)
		return (NULL);
	if (!env[0])
		return (empty_env());
	path_var = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			path_var = env[i];
			break ;
		}
		i++;
	}
	if (!path_var)
		return (empty_env());
	result = ft_split(path_var + 5, ':');
	return (result);
}

void	work_child(t_all *data, int i)
{
	char	*true_path;
	t_cmd	*cmd;

	cmd = &data->all_cmds[i];
	if (g_sig)
		end_clean(data, NULL, 0);
	true_path = setup_child(cmd, data);
	if (!is_regular_file(true_path))
		end_clean(data, NULL, 126);
	execve(true_path, cmd->args, data->envp);
	free(true_path);
	end_clean(data, true_path, errno);
}

static
	int	wait_all(int nb)
{
	int	res;
	int	status;
	int	i;

	i = 0;
	res = 0;
	while (i < nb)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			res = WEXITSTATUS(status);
		i++;
	}
	return (res);
}

static
	int	cmd_precheck(t_all *data)
{
	if (!data->all_cmds || !data->all_cmds[0].args)
		return (0);
	if (!data->all_cmds[0].args[0] && !data->all_cmds[0].token)
		return (0);
	else if (!data->all_cmds[0].args[0] && data->all_cmds[0].token)
	{
		if (!set_reverse_redir(data))
			return (0);
	}
	if (!data->all_cmds[0].args[0] || !data->all_cmds[0].args[0][0])
		return (0);
	if (!ft_strncmp(data->all_cmds[0].args[0], "exit", 4))
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		end_clean(data, NULL, 0);
	}
	return (1);
}

void	handle_exec(t_all *data)
{
	int	i;
	int	j;
	int	i_skip_files;

	i = 0;
	j = 0;
	if (!cmd_precheck(data))
		return ;
	while ((i < data->nb_cmds) && !g_sig)
	{
		i_skip_files = set_io(data, i);
		if (g_sig || !launch_process(data, i, &j))
			break ;
		close_both_fds(&data->all_cmds[i]);
		i = i_skip_files + 1;
	}
	data->last_exitcode = wait_all(j);
}
