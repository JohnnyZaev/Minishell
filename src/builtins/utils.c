/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 13:57:58 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/23 12:36:52 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	execute_builtins(t_minishell *m_shell, char *str, int id)
{
	if (id == 1)
		my_cd(m_shell, str + 3);
	if (id == 2)
		my_echo(str + 5);
	if (id == 3)
		env(m_shell->envs);
	if (id == 4)
		my_exit(str + 5);
	if (id == 5)
		my_export(m_shell, str + 6);
	if (id == 6)
		my_pwd();
	if (id == 7)
		unset(m_shell, str + 6);
	return (1);
}

int	builtints_handler(t_minishell *m_shell, char *str)
{
	int	exit_status;

	exit_status = 0;
	if (!(strncmp(str, "cd", 2)) && (str[2] == ' ' || str[2] == 0))
		exit_status = 1;
	if (!(strncmp(str, "echo", 4)) && (str[4] == ' ' || str[4] == 0))
		exit_status = 2;
	if (!(strncmp(str, "env", 3)) && (str[3] == ' ' || str[3] == 0))
		exit_status = 3;
	if (!(strncmp(str, "exit", 4)) && (str[4] == ' ' || str[4] == 0))
		exit_status = 4;
	if (!(strncmp(str, "export", 6)) && (str[6] == ' ' || str[6] == 0))
		exit_status = 5;
	if (!(strncmp(str, "pwd", 3)) && (str[3] == ' ' || str[3] == 0))
		exit_status = 6;
	if (!(strncmp(str, "unset", 5)) && (str[5] == ' ' || str[5] == 0))
		exit_status = 7;
	if (exit_status)
		return (execute_builtins(m_shell, str, exit_status));
	return (exit_status);
}
