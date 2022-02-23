/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:59:10 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 17:40:33 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_echo(char *str_exe)
{
	bool	flag;
	char	**str_split;
	int		i;

	flag = true;
	if (str_exe[0])
	{
		str_split = ft_split(str_exe, ' ');
		if (!str_split)
			exit(error(1));
		i = 0;
		if (!(ft_strncmp(str_split[i], "-n", 3)))
		{
			flag = false;
			i++;
		}
		while (str_split[i])
		{
			printf("%s", str_split[i]);
			if (str_split[i + 1])
				printf(" ");
			i++;
		}
		i = 0;
		while (str_split[i])
		{
			free(str_split[i]);
			i++;
		}
		free(str_split);
	}
	if (flag)
		printf("\n");
}
