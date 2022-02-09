/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:28:18 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/09 12:57:46 by gvarys           ###   ########.fr       */
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

typedef struct s_envs
{
	char			*key;
	char			*value;
	struct s_envs	*next;
}	t_envs;

typedef struct s_minishell
{
	t_envs	*envs;
}	t_minishell;

//minishell_utils.c
char	*ft_exist(char **envp, char *cmd);
int		ft_dup(int old, int newfd);
int		ft_fork(void);
//pipes_and_pids.c
int		**ft_piping(int count);
int		*ft_piding(int count);
//envp.c
void	envp_to_dict(t_envs **envs, char **envp);
char	*search_envs(t_envs **envs, char *key);
//signals
void	start_signals(void);

//readline prototypes
void	rl_replace_line(const char *text, int clear_undo);

//errors
int		error(int err);

#endif