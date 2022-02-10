/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/10 11:39:21 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	int		pid1;
	int		pid2;
	int		pipe[2];

	(void) argc;
	// (void) argv;
	(void) envp;
	while (true)
	{
		str = readline("minishell$");
		ft_pipe(pipe);
		pid1 = ft_fork();
		if (pid1 == 0)
		{
			read_redirect(1, argv[1]);
			ft_dup(pipe[1], 1);
			close(pipe[0]);
			close(pipe[1]);
			execute_process(argv[2], envp);
		}
		pid2 = ft_fork();
		if (pid2 == 0)
		{
			write_redirect(pipe[0], argv[4]);
			ft_dup(pipe[0], 0);
			close(pipe[0]);
			close(pipe[1]);
			execute_process(argv[3], envp);
		}
 		close(pipe[0]);
 		close(pipe[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
		free(str);
	}
	return (0);
}
