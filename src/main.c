/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/02 15:48:09 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exe_handler(t_minishell	*m_shell, char *str)
{
	t_str_exe	*buf;
	t_pipes		pipex;
	int			i;

    parse_str(m_shell, str);
	ft_memset(&pipex, 0, sizeof(pipex));
	print_str_exe(m_shell->str_exe);
	pipex.pid_count = pids_counter(m_shell);
	pipex.pipe_count = pipes_counter(m_shell);
	pipex.pipes = ft_piping(pipex.pipe_count);
	pipex.pids = ft_piding(pipex.pid_count);
	buf = m_shell->str_exe;
	i = 0;
	while (i < pipex.pid_count && buf)
	{
		executable(m_shell, buf, &pipex, i);
		buf = get_next_pipe(buf);
		i++;
	}
	i = -1;
	close_unusedpipes(pipex.pipes, -1, -1, pipex.pipe_count);
	while (++i < pipex.pid_count)
		waitpid(pipex.pids[i], NULL, 0);
	i = 0; 
	while (i < pipex.pipe_count + 1 && pipex.pipe_count)
	{
		free(pipex.pipes[i]);
		pipex.pipes[i] = NULL;
		i++;
	}
	if (pipex.pipe_count)
	{
		free(pipex.pipes);
		pipex.pipes = NULL;
	}
	free(pipex.pids);
	pipex.pids = NULL;
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
		exe_handler(&m_shell, str);
		free(str);	
		free_str_exe(m_shell.str_exe);
		m_shell.str_exe = NULL;
	}
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*str;
// 	t_minishell	m_shell;

// 	(void) argc;
// 	str = argv[1];
//     // str = "\"ls\" pwd\"<file3\"fe$PWDefwg4 <file2 | wc";
//     // str = "\"$HOME $PWD\"pwd";
//     // str = "'$HOSTNAME' '$PWD '";
//     str = "$HOME_$PWD"; //1
// 	memset(&m_shell, 0, sizeof(m_shell));
// 	envp_to_dict(&m_shell.envs, envp);
// 	exe_handler(&m_shell, str);
// 	free_str_exe(m_shell.str_exe);
// 	m_shell.str_exe = NULL;
// 	return (0);
// }
