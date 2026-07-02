/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:35:40 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/01 16:23:42 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_sig = 0;

static
	int	cpy_envp(char **og_envp, t_all *data)
{
	int		i;

	i = 0;
	if (!og_envp[0])
	{
		data->envp = empty_env();
		if (!data->envp)
			return (perror("empty_env"), 0);
	}
	while (og_envp[i])
		i++;
	data->envp = malloc((i + 1) * (sizeof(char *)));
	if (!data->envp)
		return (perror("cpy_envp"), 0);
	if (!cpy_args_to_args(og_envp, data->envp))
		return (free_array_null_end(data->envp), perror("cpy_args_to_args"), 0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_all	data;

	interactive_sig1();
	(void)ac;
	(void)av;
	init_struct_null(&data);
	if (!cpy_envp(envp, &data))
		return (1);
	while (1)
	{
		interactive_sig1();
		data.full_line = readline("minishell$ ");
		if (!data.full_line)
			end_clean(&data, NULL, 0);
		g_sig = 0;
		interactive_sig2();
		add_history(data.full_line);
		if (!handle_parsing(&data))
			end_clean(&data, "handle_parsing", 1);
		handle_exec(&data);
		clean_all(&data);
	}
}
