/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:59:10 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/15 18:37:38 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_echo(t_str_exe *str_exe)
{
	bool	flag;
	
	flag = true;
	if (str_exe && str_exe->str_exe && ft_strncmp(str_exe->str_exe, "-n", 3))
		flag = false;
	while (str_exe && !str_exe->type)
	{
		printf("%s", str_exe->str_exe);
		if (str_exe->next && !str_exe->next->type)
			printf(" ");
		str_exe = str_exe->next;
	}
	if (flag)
		printf("\n");
	
}
