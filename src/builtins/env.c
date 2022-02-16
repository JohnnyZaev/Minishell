/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:08:28 by gvarys            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/16 13:28:31 by ereginia         ###   ########.fr       */
=======
/*   Updated: 2022/02/16 15:25:29 by gvarys           ###   ########.fr       */
>>>>>>> 108fb5e0b4e12a39fe637b5b6594527d9e88ca9a
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
