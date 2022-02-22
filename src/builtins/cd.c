/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:30:05 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 16:00:56 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_pwds(t_minishell *m_shell, char *old_pwd, char *new_pwd)
{
	char	*old_str;
	char	*new_str;

	remove_envs(&m_shell->envs, "PWD");
	remove_envs(&m_shell->envs, "OLDPWD");
	old_str = ft_strjoin("OLDPWD=", old_pwd);
	new_str = ft_strjoin("PWD=", new_pwd);
	if (!old_str || !new_str)
		exit(error(1));
	parce_envp(&m_shell->envs, old_str);
	parce_envp(&m_shell->envs, new_str);
	free(old_str);
	free(new_str);
}

static bool	home_cd(t_minishell *m_shell)
{
	char	*home;

	home = search_envs(&m_shell->envs, "HOME");
	if (!home)
	{
		printf("minishell $ cd: HOME not set");
		return (false);
	}
	else
	{
		if (chdir(home) == -1)
		{
			printf("minishell $ cd: No such file or directory\n");
			return (false);
		}
	}
	return (true);
}

void	my_cd(t_minishell *m_shell, char *str_exe)
{
	char	old_pwd[PATH_MAX + 1];
	char	new_pwd[PATH_MAX + 1];
	char	*norm_status;

	norm_status = getcwd(old_pwd, PATH_MAX + 1);
	if (!norm_status)
		exit(error(3));
	if (!str_exe)
	{
		if (!home_cd(m_shell))
			exit(1);
	}
	else
	{
		if (chdir(str_exe) == -1)
		{
			printf("minishell $ cd: No such file or directory\n");
			exit(1);
		}
	}
	norm_status = getcwd(new_pwd, PATH_MAX + 1);
	if (!norm_status)
		exit(error(3));
	update_pwds(m_shell, old_pwd, new_pwd);
}
