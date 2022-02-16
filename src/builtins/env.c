/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:08:28 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/16 16:48:30 by ereginia         ###   ########.fr       */
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
}
