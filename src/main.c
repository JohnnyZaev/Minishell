/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/08 11:08:50 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		//execute_process(str, envp);
		free(str);
	}
	return (0);
}
