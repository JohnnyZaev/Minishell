/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:59:10 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 15:21:31 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_echo(char *str_exe)
{
	bool	flag;
	char	**str_split;
	int		i;

	flag = true;
	str_split = ft_split(str_exe, ' ');
	if (!str_split)
		exit(error(1));
	if (str_split[0] && str_split[1] && ft_strncmp(str_split[0], "-n", 3))
		flag = false;
	i = 0;
	if (flag)
		i++;
	while (str_split[i])
	{
		printf("%s", str_split[i]);
		if (str_split[i + 1])
			printf(" ");
		i++;
	}
	if (flag)
		printf("\n");
	i = 0;
	while (str_split[i])
	{
		free(str_split[i]);
		i++;
	}
	free(str_split);
}
