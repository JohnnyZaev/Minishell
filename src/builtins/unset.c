/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:27:46 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 15:59:25 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset(t_minishell *m_shell, char *str_exe)
{
	if (!valid_chars_in_env(str_exe))
	{
		printf("minishell $ unset: not a valid identifier\n");
	}
	else
		remove_envs(&m_shell->envs, str_exe);
}
