/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:08:28 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/04 14:53:04 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_envs *envs)
{
	while (envs)
	{
		printf("%s=%s\n", envs->key, envs->value);
		envs = envs->next;
	}
	exit(0);
}
