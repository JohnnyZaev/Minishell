/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:28:18 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/10 15:53:48 by ereginia         ###   ########.fr       */
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
# define REDIRECT 2
# define BIN 3

typedef struct s_str_exe
{
	char	*str_exe;
	int		type;
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
char	*ft_exist(char **envp, char *cmd);
int		ft_dup(int old, int newfd);
int		ft_fork(void);
//pipes_and_pids.c
int		**ft_piping(int count);
int		*ft_piding(int count);
void	ft_pipe(int *fd);
void	pipe_welding(int *pipe1, int *pipe2);
//execute_and_redirects.c
void	execute_process(char *c_line, char **envp);
void	read_redirect(int fd_out, char *file_path);
void	write_redirect(int fd_in, char *file_path);
void	read_heredoc_process(char *stop, int fd);
//envp.c
void	envp_to_dict(t_envs **envs, char **envp);
char	*search_envs(t_envs **envs, char *key);
//signals
void	start_signals(void);

//readline prototypes
void	rl_replace_line(const char *text, int clear_undo);

//errors
int		error(int err);

//SHIT PARSER
void	parse_str(t_minishell *m_shell, char *str);

//ft_split_max.c
char	**ft_split_max(char *str, char *charset);

#endif