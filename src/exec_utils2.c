/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:55:40 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/01 16:56:01 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	autodup_heredoc(void)
{
	int	fd;

	fd = open("here_doc", O_RDONLY);
	if (fd < 0)
	{
		perror("autodup_heredoc");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) < 0)
		perror("autodup_heredoc");
	close(fd);
}

int	cpy_args_to_args(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (0);
		i++;
	}
	if (i)
		dest[i] = NULL;
	return (1);
}

int	set_reverse_redir(t_all *data)
{
	int	i;
	int	size;

	i = 1;
	while (1)
	{
		if (data->all_cmds[i].args[1])
			break ;
		if (!data->all_cmds[i].token || data->all_cmds[i].token == 1240)
			return (ft_putstr_fd("minishell: syntax error\n", 2), 0);
		i++;
	}
	free(data->all_cmds[0].args);
	size = 0;
	while (data->all_cmds[i].args[size])
		size++;
	data->all_cmds[0].args = malloc((sizeof(char *)) * (size));
	if (!data->all_cmds[0].args)
		return (0);
	if (!cpy_args_to_args(&data->all_cmds[i].args[1], data->all_cmds[0].args))
		return (perror("cpy_args_to_args"), 0);
	return (1);
}

char	*setup_child(t_cmd *cmd, t_all *data)
{
	char	*true_path;
	char	**paths;

	autodup(&cmd->fd_in, STDIN_FILENO);
	autodup(&cmd->fd_out, STDOUT_FILENO);
	clean_all_fds(data);
	if (!ft_strncmp(cmd->args[0], "exit", 4))
		end_clean(data, NULL, 0);
	if (handle_builtins_child(cmd->args, data))
		end_clean(data, NULL, 0);
	paths = get_paths(data->envp);
	if (!paths)
		end_clean(data, "get_paths", 1);
	true_path = try_paths(paths, cmd->args[0], data);
	free_array_null_end(paths);
	if (!true_path)
		end_clean(data, NULL, 1);
	return (true_path);
}
