/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:13 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/23 17:37:08 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_envp(t_envs *envs)
{
	char	**result;
	char	*temp;
	t_envs	*buf;
	int		words;

	words = 0;
	buf = envs;
	while (buf)
	{
		buf = buf->next;
		words++;
	}
	result = (char **)malloc(sizeof(char *) * (words + 1));
	words = 0;
	buf = envs;
	while (buf)
	{
		temp =  ft_strjoin(buf->key, "=");
		result[words] = ft_strjoin(temp, buf->value);
		free(temp);
		buf = buf->next;
		words++;
	}
	result[words] = NULL;
	return (result);
}