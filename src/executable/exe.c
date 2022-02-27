/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 12:09:59 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/27 13:26:15 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	buildins_or_binary(t_minishell *m_shell, t_str_exe *buf)
{
	while (buf)
	{
		if (buf->type < 3 && builtints_handler(m_shell, buf->str_exe, true))
			exit(1);
		if (buf->type < 3)
			execute_process(buf->str_exe, m_shell);
		buf = buf->next;
	}
}

static void	redirect_handle(t_str_exe *buf)
{
	while (buf && buf->type != 2 && buf->type != 1)
	{
		if (buf->type == 3)
			read_redirect(buf->str_exe);
		else if (buf->type == 4)
			write_redirect(buf->str_exe, 4);
		else if (buf->type == 6)
			write_redirect(buf->str_exe, 6);
		buf = buf->next;
	}
}

static void	pipe_laying(t_str_exe *str_exec, t_pipes *pipex, int pipe_id)
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
}

void	executable(t_minishell *m_shell, t_str_exe *str_exec,
	t_pipes *pipex, int i)
{
	int			pipe_id;

	pipe_id = which_pipe(str_exec);
	if (builtints_handler(m_shell, str_exec->str_exe, false))
		return ;
	pipex->pids[i] = ft_fork();
	if (pipex->pids[i] == 0)
	{
		if (get_next_pipe(str_exec) && get_next_pipe(str_exec)->prev->type == 5)
			read_heredoc_process(get_next_pipe(str_exec)->prev->str_exe,
				pipex->pipes[pipe_id][1]);
		pipe_laying(str_exec, pipex, pipe_id);
		redirect_handle(str_exec);
		buildins_or_binary(m_shell, str_exec);
		exit(1);
	}
	if (str_exec && (str_exec->type == 2 || str_exec->type == 0
			|| (get_next_pipe(str_exec)
				&& get_next_pipe(str_exec)->prev->type == 5)))
	{
		close_unusedpipes(pipex->pipes, -1, -1, pipe_id);
		waitpid(pipex->pids[i], NULL, 0);
	}
}
