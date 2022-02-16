/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:02:39 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/13 12:05:00 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **tofree)
{
	int i;

	i = 0;
	while(tofree[i])
	{
		free(tofree[i]);
		i++;
	}
	free(tofree);
}
