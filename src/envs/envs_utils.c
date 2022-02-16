/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:31:08 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/15 12:56:45 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	valid_chars_in_env(char *key)
{
	if (key && (ft_isalpha(*key) || *key == '_'))
		key++;
	else
		return (false);
	while (*key && *key != '=')
	{
		if (ft_isalnum(*key) || *key == '_')
			key++;
		else
			return (false);
	}
	return (true);
}

static void	free_one_env(t_envs *envs)
{
	free(envs->key);
	free(envs->value);
	free(envs);
}

void	remove_envs(t_envs **envs, char *key)
{
	t_envs	*save;
	t_envs	*temp;

	if (!envs || !(*envs) || !key)
		return ;
	temp = *envs;
	if (!(ft_strncmp(temp->key, key, ft_strlen(key) + 1)))
	{
		save = temp->next;
		free_one_env(temp);
		*envs = save;
	}
	while (temp && temp->next)
	{
	if (!(ft_strncmp(temp->next->key, key, ft_strlen(key) + 1)))
	{
		save = temp->next->next;
		free_one_env(temp->next);
		temp->next = save;
	}
	temp = temp->next;
	}
}