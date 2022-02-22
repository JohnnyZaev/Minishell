/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 12:07:30 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void print_str_exe(t_str_exe *str_exe)
{
	t_str_exe *buf;

	buf = str_exe;
	while (buf)
	{
		printf("STR -> %s, TYPE -> %d\n", buf->str_exe, buf->type);
		buf = buf->next;
	}
}

void	exe_handler(t_minishell	*m_shell, char *str, char **envp)
{
	t_str_exe	*buf;
	t_pipes		pipex;
	int         i;

	(void)envp;
    parse_str(m_shell, str);
	print_str_exe(m_shell->str_exe);
	pipex.pid_count = pids_counter(m_shell);
	pipex.pipe_count = pipes_counter(m_shell);
	pipex.pipes = ft_piping(pipex.pipe_count);
	pipex.pids = ft_piding(pipex.pid_count);
	buf = m_shell->str_exe;
	i = 0;
	while (i < pipex.pid_count && buf)
	{
		executable(buf, envp, &pipex, i);
		buf = get_next_pipe(buf);
		i++;
	}
	i = -1;
	close_unusedpipes(pipex.pipes, -1, -1, pipex.pipe_count);
	while (++i < pipex.pid_count)
		waitpid(pipex.pids[i], NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_minishell	m_shell;

	(void) argc;
	(void) argv;
	ft_memset(&m_shell, 0, sizeof(m_shell));
	envp_to_dict(&m_shell.envs, envp);
	while (true)
	{
		start_signals();
		str = readline("minishell $ ");
		if (!str)
			exit(printf("\033[Aminishell $ exit\n"));
		add_history(str);
		exe_handler(&m_shell, str, envp);
		free(str);
		free_str_exe(m_shell.str_exe);
		m_shell.str_exe = NULL;
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_minishell	m_shell;
// 	t_str_exe	*buf;
// 	int		    **pipes;
// 	int		    *pids;
// 	int         i = 0;

// 	(void)argc;
//     memset(&m_shell, 0, sizeof(m_shell));
//     parse_str(&m_shell, argv[1]);
// 	print_str_exe(m_shell.str_exe);
// 	pipes = ft_piping(pipes_counter(&m_shell));
// 	pids = ft_piding(pids_counter(&m_shell));
// 	buf = m_shell.str_exe;
// 	while (i < pids_counter(&m_shell))
// 	{
// 	    // printf("pipe exist %d\n", pipe_type(buf));
// 	    executable(buf, envp, &pids[i], pipes);
// 	    buf = get_next_pipe(buf);
// 	    i++;
// 	}
// 	i = -1;
// 	close_unusedpipes(pipes, -1, -1, pipes_counter(&m_shell));
// 	while (++i < pids_counter(&m_shell))
// 	    waitpid(pids[i], NULL, 0);
//     return (0);
// }
