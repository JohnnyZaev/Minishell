/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 12:45:45 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/09 13:29:37 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//err - exit status + message to STDERR
int	error(int err)
{
	if (err == 1)
		write(2, "Malloc error\n", 13);
	return (err);
}
