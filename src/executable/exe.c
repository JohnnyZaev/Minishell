/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:09:59 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/23 17:18:32 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int pids_counter(t_minishell	*m_shell)
{
    t_str_exe   *buf;
    int         pids;

    pids = 1;
    buf = m_shell->str_exe;
    while(buf)
    {
        if (buf->type == 1 || buf->type == 2)
            pids++;
        buf = buf->next;
    }
    if (buf == m_shell->str_exe)
        return 0;
    return pids;
}

int pipes_counter(t_minishell	*m_shell)
{
    t_str_exe   *buf;
    int         pipes;
    
    pipes = 0;
    buf = m_shell->str_exe;
    while(buf)
    {
        if (buf->type == 1)
            pipes++;
        buf = buf->next;
    }
    return pipes;
}

t_str_exe   *get_next_pipe(t_str_exe *str_exec)
{
    while (str_exec && str_exec->type > 2)
        str_exec = (str_exec)->next;
    return (str_exec->next);
}

int pipe_type(t_str_exe *str_exec)
{
    int         i;
    int         j;
    t_str_exe	*buf;
    
    buf = str_exec;
    if (buf->prev)
        i = (buf->prev->type == 1);
    else
        i = 0;
    while (buf && buf->type > 2)
        buf = buf->next;
    j = (buf->type == 1);
    return (i + 2 * j);
}

int	which_pipe(t_str_exe *str_exec)
{
	t_str_exe	*buf;
	int			count;

	count = 0;
	buf = str_exec;
	while (buf)
	{
		if (buf->prev && buf->prev->type == 1)
			count++;
		buf = buf->prev;
	}
	return (count);
}

void	executable(t_minishell	*m_shell, t_str_exe *str_exec, t_pipes *pipex, int i)
{
	t_str_exe	*buf;
	int			pipe_id;

	pipe_id = which_pipe(str_exec);
	buf = str_exec;
	if (builtints_handler(m_shell, buf->str_exe))
		return ;
	pipex->pids[i] = ft_fork();
	if (pipex->pids[i] == 0)
	{
		if (pipe_type(str_exec) == 2)
		{
			ft_dup(pipex->pipes[pipe_id][1], 1);
			close_unusedpipes(pipex->pipes, -1, -1, pipex->pipe_count);
		}
		else if (pipe_type(str_exec) == 1)
		{
			ft_dup(pipex->pipes[pipe_id - 1][0], 0);
			close_unusedpipes(pipex->pipes, -1, -1, pipex->pipe_count);
		}
		else if (pipe_type(str_exec) == 3)
		{
			ft_dup(pipex->pipes[pipe_id][1], 1);
			ft_dup(pipex->pipes[pipe_id - 1][0], 0);
			close_unusedpipes(pipex->pipes, -1, -1, pipex->pipe_count);
		}
		while(buf && buf->type != 2 && buf->type != 1)
		{
			if (buf->type == 3)
				read_redirect(buf->str_exe);
			else if (buf->type == 4)
				write_redirect(buf->str_exe, 4);
			else if (buf->type == 6)
				write_redirect(buf->str_exe, 6);
			buf = buf->next;
		}
		buf = str_exec;
		while(buf)
		{
			if (buf->type < 3)
				execute_process(buf->str_exe, m_shell);
			buf = buf->next;
		}
		exit(1);
	}
	if (buf && (buf->type == 2 || buf->type == 0))
	{
		close_unusedpipes(pipex->pipes, -1, -1, pipe_id);
		waitpid(pipex->pids[i], NULL, 0);
	}
}
