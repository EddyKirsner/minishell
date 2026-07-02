/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:33:39 by ktaouach          #+#    #+#             */
/*   Updated: 2025/04/05 15:56:29 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

typedef struct s_cmd
{
	char	**args;
	char	*cut_line;
	int		token;
	int		excode;
	int		fd_in;
	int		fd_out;
	char	***envp_ptr;
	int		x;
}			t_cmd;

typedef struct s_all
{
	char	*full_line;
	int		nb_cmds;
	t_cmd	*all_cmds;
	int		last_exitcode;
	char	**envp;
}		t_all;

extern volatile sig_atomic_t	g_sig;

//signal
void	sigint_handler1(int signal);
void	sigint_handler2(int signal);
void	sigquit_handler(int signal);

void	interactive_sig1(void);
void	interactive_sig2(void);
void	interactive_sig_heredoc(void);

//cleaning
void	free_array_null_end(char **array);
void	close_both_fds(t_cmd *cmd);
void	clean_all_fds(t_all *data);
void	free_structs(t_all *data, int limit);
void	clean_all(t_all *data);
void	end_clean(t_all *data, char *error, int exit_code);

//parsing1
void	init_struct_null(t_all *data);
void	flag_preparse(char *str);
int		is_whitespace(char c);
int		is_in_quote(char *str, int i);
char	**ft_split_quotes(char const *s);
int		check_if_operator(char *str, int *j);
int		syntax_check(t_all *data);
void	fill_cmds_null(t_all *data);
int		count_commands(char *str);
void	replace_preparse(char *str);
int		quotes_delete(char *str);
void	remove_chars(char *str);
void	delete_bad_chars(char *str, int mode);
void	handler_delete_chars(t_all *data);

//expand
void	init_3_int(int *i, int *y, int *index);
void	init_3_int2(int *i, int *y, int *x);
void	increment_2_int(int *i, int *y);
void	check_incr(char *str, int *i);
char	*ft_malloc_error_expand(char **var_tab, int ok);
int		count_env_var(char *str);
int		allocate_var(char *str, char **var_tab);
void	write_var(char *str, char **var_tab);
char	*ft_free_expand(char **var_tab, int index, char *backup_freez);
char	*expand_int(char *str, int nb);
char	*expand_str(char *str, char **env_copy);
int		replace_by_expand(char **tab, int i, int exit_code, char **env);
char	*write_false_var(char *var_tab, char *str, int *y);
int		count_without(char *str);
char	*ft_just_env(char *to_cut);
int		ft_count_and_free(char *str);
void	write_and_increment(char *new_str, char *str, int *i, int *y);
char	*ft_free_and_return(char *str);
char	*ft_close_and_return(char *str, int i);
int		ft_count_and_free0(int *full_lenght, char *env_copy);
int		ft_fail_memory(void);

//parsing2
int		handle_parsing(t_all *data);
int		cpy_args_to_args(char **src, char **dest);
int		set_reverse_redir(t_all *data);

//io
int		set_output(t_cmd *cmds, int i, int *in, int *out);
int		set_input(t_cmd *cmds, int i, int *in, int *out);
void	set_pipe(t_all *data, int new_i, int i);
int		set_io(t_all *data, int i);

//builtins
void	export_alpha_sorter(char **env);
int		ft_count_envline(char **env);
void	ft_env_copy2(char **env, char **envcopy, int add);
void	free_env(char **env);
int		ft_update_pwd2(char ***env_copy, char *env_var);
int		ft_strstr_env(char **env, char *little);
int		update_env(char ***env_copy, int y, char *env_var);
int		add_env_var(char ***env_copy, char *env_var);
int		ft_update_pwd(char ***env_copy, char *old_pwd, char *path);

int		ft_cd(char *path, char ***env_copy);
int		ft_unset(char ***env, char **arg);
int		ft_export(char ***env_copy, char **env_var);
int		ft_echo(char **arg);
void	ft_pwd(void);
void	ft_print_env(char **env);
void	print_all_export(char **env);

int		handle_builtins_parent(char **args, t_all *data);
int		handle_builtins_child(char **args, t_all *data);

//exec
void	autodup(int *to_inject_in, int to_replace);
void	autodup_heredoc(void);
char	**get_paths(char **env);
char	**empty_env(void);
char	*try_paths(char **paths, char *arg, t_all *data);
int		is_regular_file(char *path);
void	work_child(t_all *data, int i);
int		launch_process(t_all *data, int i, int *cmd_count);
char	*setup_child(t_cmd *cmd, t_all *data);
void	handle_exec(t_all *data);

#endif
