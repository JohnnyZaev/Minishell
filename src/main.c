/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:38:16 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/07 16:41:30 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(void)
{
    char *str;
    while (1)
    {
        str = readline("minishell $ ");
        //execute_process(str, envp);
        free(str);
    }
	return (0);
}
