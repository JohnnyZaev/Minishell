/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/16 15:23:14 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_str_exe(t_str_exe *str_exe)
{
	t_str_exe	*buf;

	buf = str_exe;
	while (buf)
	{
		printf("STR -> %s, TYPE -> %d\n", buf->str_exe, buf->type);
		buf = buf->next;
	}
}

void	executable(t_minishell *m_shell, char **envp)
{
	int			pid;
	t_str_exe	*buf;

	pid = ft_fork();
	buf = m_shell->str_exe;
	if (pid == 0)
	{
		while (buf && buf->type != 2)
		{
			if (buf->type == 3)
				read_redirect(buf->str_exe);
			buf = buf->next;
		}
		buf = m_shell->str_exe;
		while (buf && buf->type != 2)
		{
			if (buf->type < 3)
				execute_process(buf->str_exe, envp);
			buf = buf->next;
		}
		exit(1);
	}
	waitpid(pid, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*str;
	t_minishell	m_shell;

	(void) argc;
	ft_memset(&m_shell, 0, sizeof(m_shell));
	envp_to_dict(&m_shell.envs, envp);
	printf("%s\n", search_envs(&m_shell.envs, argv[1]));
	while (true)
	{
		start_signals();
		str = readline("minishell $ ");
		if (!str)
			exit(printf("\033[Aminishell $ exit\n"));
		add_history(str);
		parse_str(&m_shell, str);
		executable(&m_shell, envp);
		free(str);
		free_str_exe(m_shell.str_exe);
		m_shell.str_exe = NULL;
	}
	return (0);
}
