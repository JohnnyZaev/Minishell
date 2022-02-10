/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/09 17:14:21 by gvarys           ###   ########.fr       */
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

//перенаправляем вывод одной трубы на вывод другой трубы
void	pipe_welding(int *pipe1, int *pipe2)
{
	close(pipe1[1]);
	ft_dup(pipe1[0], 0);
	close(pipe1[0]);
	close(pipe2[0]);
	ft_dup(pipe2[1], 1);
	close(pipe2[1]);
}

//запускает бинарник
void	execute_process(char *c_line, char **envp)
{
	int		fork_id;
	char	**arg_vec1;

	fork_id = fork();
	if (fork_id == 0)
	{
		arg_vec1 = ft_split(c_line, ' ');
		execve(ft_exist(envp, arg_vec1[0]), arg_vec1, NULL);
		exit(EXIT_SUCCESS);
	}
	waitpid(fork_id, NULL, 0);
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
