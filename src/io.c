/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:32:55 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/03 18:25:24 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static
	char	*handle_heredoc_input(char **env, char *end, int ex)
{
	char	*str;

	ft_putstr_fd("> ", STDOUT_FILENO);
	interactive_sig_heredoc();
	str = get_next_line(STDIN_FILENO);
	interactive_sig2();
	if (g_sig)
		return (free(str), NULL);
	if (!str)
	{
		ft_putstr_fd("\nminishell: here_document issue (EOF or GNL issue)", 2);
		return (write(STDOUT_FILENO, "\n", 1), NULL);
	}
	flag_preparse(str);
	if (!ft_strncmp(end, str, ft_strlen(end))
		|| !replace_by_expand(&str, 0, ex, env))
		return (free(str), NULL);
	delete_bad_chars(str, 1);
	replace_preparse(str);
	return (str);
}

static
	int	here_doc(char *end, int excode, char ***env_ptr)
{
	int		fd;
	char	*str;

	fd = open("here_doc", O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd < 0)
		return (-1);
	while (1)
	{
		str = handle_heredoc_input(*env_ptr, end, excode);
		if (!str)
			return (close(fd), -2);
		if (write(fd, str, ft_strlen(str)) != (ssize_t)ft_strlen(str))
			return (free(str), close(fd), -1);
		free(str);
	}
	return (-1);
}

int	set_output(t_cmd *cmds, int i, int *in, int *out)
{
	int	token;

	token = cmds[i].token;
	if (cmds[i].x && (token == 620 || token == 625))
	{
		i++;
		if (token == 620)
			*out = open(cmds[i].args[0], O_WRONLY | O_TRUNC | O_CREAT, 0777);
		else
			*out = open(cmds[i].args[0], O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (*out < 0)
			perror("set_output");
	}
	if (cmds[i].x && (cmds[i].token == 620 || cmds[i].token == 625))
		return (close(*out), set_output(cmds, i, in, out));
	if (cmds[i].x && (cmds[i].token == 600 || cmds[i].token == 605))
		return (set_input(cmds, i, in, out));
	return (i);
}

int	set_input(t_cmd *cmds, int i, int *in, int *out)
{
	int	token;

	token = cmds[i].token;
	if (cmds[i].x && (token == 600 || token == 605))
	{
		i++;
		if (*in >= 0)
			close(*in);
		if (token == 600)
			*in = open(cmds[i].args[0], O_RDONLY);
		else
			*in = here_doc(cmds[i].args[0], cmds[i].excode, cmds[i].envp_ptr);
		if (*in == -1)
			perror("set_input");
	}
	if (g_sig)
		return (i);
	if (cmds[i].x && (cmds[i].token == 600 || cmds[i].token == 605))
		return (close(*in), set_input(cmds, i, in, out));
	if (cmds[i].x && (cmds[i].token == 620 || cmds[i].token == 625))
		return (set_output(cmds, i, in, out));
	return (i);
}

//new_i: new index after skipping files
int	set_io(t_all *data, int i)
{
	int	new_i;
	int	*in;
	int	*out;

	in = &data->all_cmds[i].fd_in;
	out = &data->all_cmds[i].fd_out;
	new_i = set_output(data->all_cmds, i, in, out);
	if (g_sig)
		return (0);
	if (data->all_cmds[new_i].x && (data->all_cmds[new_i].token == 1240))
		set_pipe(data, new_i, i);
	return (new_i);
}
