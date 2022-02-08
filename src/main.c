/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/08 12:22:37 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
void    execute_process(char *c_line, char **envp)
{
    int     fork_id;
    char	**argVec1;

    fork_id = fork();
    if (fork_id == 0)
    {
	    argVec1 = ft_split(c_line, ' ');
	    execve(ft_exist(envp, argVec1[0]), argVec1, NULL);
        exit(EXIT_SUCCESS);
    }
    waitpid(fork_id, NULL, 0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_minishell	m_shell;

	ft_memset(&m_shell, 0, sizeof(m_shell));
	(void) argc;
	(void) argv;
	m_shell.m_envp = envp;
	while (true)
	{
		str = readline("minishell $ ");
		execute_process(str, envp);
		free(str);
	}
	return (0);
}
