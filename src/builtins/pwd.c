/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:53:52 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/22 17:07:41 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	my_pwd(void)
{
	char	pwd[PATH_MAX + 1];
	
	if (!getcwd(pwd, PATH_MAX + 1))
		exit(error(3));
	printf("%s\n", pwd);
}
