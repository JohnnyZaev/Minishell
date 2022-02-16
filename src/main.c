/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/16 11:04:14 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void print_str_exe(t_str_exe *str_exe)
{
	while (str_exe)
	{
		printf("STR -> %s, TYPE -> %d\n", str_exe->str_exe, str_exe->type);
		str_exe = str_exe->next;
	}
}

// static void	ft_tty_mask(void)
// {
// 	struct termios	sterm;

// 	tcgetattr(0, &sterm);
// 	sterm.c_lflag &= ~ECHOCTL;
// 	tcsetattr(0, 0, &sterm);
// }

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
		// ft_tty_mask();
		start_signals();
		str = readline("minishell $ ");
		if (!str)
			exit(printf("\033[Aminishell $ exit\n"));
		add_history(str);
		parse_str(&m_shell, str);
		print_str_exe(m_shell.str_exe);
		// execute_process(str, envp);
		// printf("%s\n", ft_exist(envp, str));
		// env(m_shell.envs);
		my_pwd(&m_shell.envs);
		free(str);
		free_str_exe(m_shell.str_exe);
	}
	return (0);
}
