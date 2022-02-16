/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:50:37 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/16 10:45:46 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_exit(t_str_exe *str_exe)
{
	if (!str_exe)
		exit(0);
	else
		exit(ft_atoi(str_exe->str_exe) % 256);
}
