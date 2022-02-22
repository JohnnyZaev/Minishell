/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:01:17 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 15:26:04 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_key(t_envs **envs, char *str_exe)
{
	int		i;
	char	*key;

	i = 0;
	while (str_exe[i] != '=')
		i++;
	key = ft_substr(str_exe, 0, i);
	if (!key)
		exit(error(1));
	if (search_envs(envs, key))
		remove_envs(envs, key);
	free(key);
}

static void	empty_handler(t_envs *envs)
{
	while (envs)
	{
		printf("declare -x %s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
}

void	my_export(t_minishell *m_shell, char *str_exe)
{
	if (!str_exe)
		empty_handler(m_shell->envs);
	else if (!valid_chars_in_env(str_exe))
	{
		printf("minishell $ unset: not a valid identifier\n");
	}
	else
	{
		check_key(&m_shell->envs, str_exe);
		parce_envp(&m_shell->envs, str_exe);
	}
}
