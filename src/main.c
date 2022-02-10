/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/10 11:50:39 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_tty_mask(void)
{
	struct termios	sterm;

	tcgetattr(0, &sterm);
	sterm.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &sterm);
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
		ft_tty_mask();
		start_signals();
		str = readline("minishell $ ");
		if (!str)
			exit(error(2));
		add_history(str);
		parse_str(&m_shell, str);
		while (m_shell.str_exe)
		{
			printf("STR -> %s, TYPE -> %d\n", m_shell.str_exe->str_exe, m_shell.str_exe->type);
			m_shell.str_exe = m_shell.str_exe->next;
		}
		execute_process(str, envp);
		free(str);
	}
	return (0);
}
