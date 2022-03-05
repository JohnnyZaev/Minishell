/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:11:33 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 15:08:42 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_flag(char *str, t_stuff *iter)
{
	if (str[iter->i] == '\'' && iter->flag == 0)
		iter->flag = 1;
	else if (str[iter->i] == '\'' && iter->flag == 1)
		iter->flag = 0;
	if (str[iter->i] == '\"' && iter->flag == 0)
		iter->flag = 2;
	else if (str[iter->i] == '\"' && iter->flag == 2)
		iter->flag = 0;
}

void	set_half_flag(char *str, t_stuff *iter)
{
	if (str[iter->i] == '\'' && iter->flag == 0)
		iter->flag = 1;
	if (str[iter->i] == '\"' && iter->flag == 0)
		iter->flag = 2;
}

void	iter_ik(t_stuff *iter)
{
	iter->i++;
	iter->k++;
}