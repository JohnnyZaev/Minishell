/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:59:10 by gvarys            #+#    #+#             */
/*   Updated: 2022/03/07 20:51:59 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	norm_helper(char **str_split, bool flag)
{
	int	i;

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
	return (flag);
}

void	my_echo(char *str_exe, t_minishell *m_shell)
{
	bool	flag;
	char	**str_split;

	flag = true;
	if (str_exe[0])
	{
		str_split = comma_killer(str_exe);
		if (!str_split)
			exit(error(1));
		flag = norm_helper(str_split, flag);
		free(str_split);
	}
	if (flag)
		printf("\n");
	m_shell->error_code = 0;
	exit(0);
}
