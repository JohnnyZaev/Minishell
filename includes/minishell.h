/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:28:18 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 15:27:58 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/syslimits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <editline/readline.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"

# define NOTHIN 0
# define PIPE 1
# define BIN 2
# define REDIRECT_IN 3
# define REDIRECT_OUT 4
# define HEREDOC 5
# define REDIRECT_AP 6

typedef struct s_pipes
{
	int	**pipes;
	int *pids;
	int	pipe_count;
	int	pid_count;
}	t_pipes;

typedef struct s_str_exe
{
	char				*str_exe;
	int					type;
	struct s_str_exe	*prev;
	struct s_str_exe	*next;
}	t_str_exe;

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}	t_envs;

typedef struct s_minishell
{
	t_envs		*envs;
	t_str_exe	*str_exe;
}	t_minishell;

//minishell_utils.c
char		*ft_exist(char *env, char *cmd);
int			ft_dup(int old, int newfd);
int			ft_fork(void);
void		ft_pipe(int *fd);
//pipes_and_pids.c
int			**ft_piping(int count);
int			*ft_piding(int count);
void		close_unusedpipes(int **pipes, int pipe_num1, int pipe_num2, int count);
void		wait_all_pids(int pids_count);

//execute_and_redirects.c
void	execute_process(char *c_line, t_envs *envs);
void	read_redirect(char *file_path);
void	write_redirect(char *file_path, int mode);
void	read_heredoc_process(char *stop, int fd);
//envp.c
void		envp_to_dict(t_envs **envs, char **envp);
char		*search_envs(t_envs **envs, char *key);
void		remove_envs(t_envs **envs, char *key);
bool		valid_chars_in_env(char *key);
void		parce_envp(t_envs **envs, char *envp);

//signals
void		start_signals(void);

//readline prototypes
void		rl_replace_line(const char *text, int clear_undo);

//errors
int			error(int err);

// parser/parser.c
int			type_searcher(char *str);
void		parse_str(t_minishell *m_shell, char *str);
void		str_exe_addback(t_str_exe **str_exe, t_str_exe *new);
void		free_str_exe(t_str_exe *str_exe);
t_str_exe	*create_str_exe(char *content);
// parser/parser_utils.c
void		parse_handler(t_minishell *m_shell, char **str);

// utils/ft_split_max.c
char	**ft_split_max(char *str, char *charset, char sep);

// utils/clean.c
void		free_split(char **tofree);

// executable/exe.c
void		executable(t_minishell	*m_shell, t_str_exe *str_exec, t_pipes *pipex, int i);
t_str_exe   *get_next_pipe(t_str_exe *str_exec);
int			pipe_type(t_str_exe *str_exec);
int			pipes_counter(t_minishell	*m_shell);
int			pids_counter(t_minishell	*m_shell);
int			which_pipe(t_str_exe *str_exec);

//builtins
void		unset(t_minishell *m_shell, t_str_exe *str_exe);
void		env(t_envs *envs);
void		my_exit(t_str_exe *str_exe);
void		my_pwd(void);
void		my_export(t_minishell *m_shell, t_str_exe *str_exe);
void		my_cd(t_minishell *m_shell, t_str_exe *str_exe);
void		my_echo(t_str_exe *str_exe);

#endif