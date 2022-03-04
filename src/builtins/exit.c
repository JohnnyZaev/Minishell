/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:50:37 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/04 16:04:44 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(char *str_exe)
{
	int	i;
	
	if (!str_exe)
		exit(0);
	else
	{
		i = 0;
		while (str_exe[i])
		{
			if (!(ft_isdigit(str_exe[i])))
			{
				printf("minishell $ : %s: numeric argument required\n", str_exe);
				exit(255);
			}
			i++;
		}
		exit(ft_atoi(str_exe) % 256);
	}
}
