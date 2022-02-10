/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:28:18 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/09 16:47:21 by ereginia         ###   ########.fr       */
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
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>
# include "../libft/libft.h"

typedef struct s_minishell
{
	char	**m_envp;
}	t_minishell;

//minishell_utils.c
char	*ft_exist(char **envp, char *cmd);
int     ft_dup(int old, int newfd);
int     ft_fork(void);
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

#endif