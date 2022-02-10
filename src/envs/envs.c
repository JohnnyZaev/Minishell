/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:53:49 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/09 12:55:29 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*search_envs(t_envs **envs, char *key)
{
	t_envs	*temp;

	if (!envs || !(*envs) || !key)
		return (0);
	temp = *envs;
	while (temp)
	{
		if ((ft_strncmp(temp->key, key, ft_strlen(temp->key) + 1)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (0);
}

static t_envs	*create_envs_dict(char *envp)
{
	int		i;
	int		j;
	t_envs	*new;

	new = (t_envs *) malloc(sizeof(t_envs));
	if (!new)
		exit(error(1));
	i = 0;
	while (envp[i] != '=')
		i++;
	new->key = ft_substr(envp, 0, i);
	if (!new->key)
		exit(error(1));
	j = i + 1;
	while (envp[j] != '\0' && envp[j] != '\n')
		j++;
	new->value = ft_substr(envp, i + 1, j - i);
	if (!new->value)
		exit(error(1));
	new->next = 0;
	return (new);
}

static void	parce_envp(t_envs **envs, char *envp)
{
	t_envs	*temp;

	if (!(*envs))
	{
		*envs = create_envs_dict(envp);
	}
	else
	{
		temp = *envs;
		while (temp->next)
			temp = temp->next;
		temp->next = create_envs_dict(envp);
	}
}

void	envp_to_dict(t_envs **envs, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		parce_envp(envs, envp[i]);
}