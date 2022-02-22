/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:57:58 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 16:01:29 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int execute_builtins(t_minishell *m_shell, char *str, int id)
{
	char *str_exe;

	if (id == 1)
	{
		str_exe = ft_substr(str, 3, ft_strlen(str));
		my_cd(m_shell, str_exe);
	}
	if (id == 2)
	{
		str_exe = ft_substr(str, 5, ft_strlen(str));
		my_echo(str_exe);
	}
	if (id == 3)
	{
		str_exe = ft_substr(str, 4, ft_strlen(str));
		env(m_shell->envs);
	}
	if (id == 4)
	{
		str_exe = ft_substr(str, 5, ft_strlen(str));
		my_exit(str_exe);
	}
	if (id == 5)
	{
		str_exe = ft_substr(str, 7, ft_strlen(str));
		my_export(m_shell, str_exe);
	}
	if (id == 6)
	{
		str_exe = ft_substr(str, 4, ft_strlen(str));
		my_pwd();
	}
	if (id == 7)
	{
		str_exe = ft_substr(str, 6, ft_strlen(str));
		unset(m_shell, str);
	}
	free(str_exe);
	exit(0);
}

int builtints_handler(t_minishell *m_shell, char *str)
{
	int	exit_status;

	exit_status = 0;
	if (!(strncmp(str, "cd ", 3)))
		exit_status = 1;
	else if (!(strncmp(str, "echo ", 5)))
		exit_status = 2;
	else if (!(strncmp(str, "env ", 4)))
		exit_status = 3;
	else if (!(strncmp(str, "exit ", 5)))
		exit_status = 4;
	else if (!(strncmp(str, "export ", 7)))
		exit_status = 5;
	else if (!(strncmp(str, "pwd ", 4)))
		exit_status = 6;
	else if (!(strncmp(str, "unset ", 6)))
		exit_status = 7;
	if (exit_status)
		execute_builtins(m_shell, str, exit_status);
	return (exit_status);
}