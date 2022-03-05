/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 13:11:33 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 15:53:55 by gvarys           ###   ########.fr       */
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

void	write_word(char *dest, char *from, int size)
{
	int	i;

	i = 0;
	while (from[i] && i < size)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	count_words_helper(char *str, t_stuff	*iter, int *words)
{
	if (char_is_separator(str[iter->i + 1]) > 0
		&& char_is_separator(str[iter->i]) == 0)
		*words++;
	if (char_is_separator(str[iter->i]) > 0
		&& char_is_separator(str[iter->i]) < 3 && !str[iter->i + 1])
		*words++;
	if (char_is_separator(str[iter->i]) > 0
		&& char_is_separator(str[iter->i + 1]) == 0)
		*words++;
	if (char_is_separator(str[iter->i]) == 2
		&& char_is_separator(str[iter->i + 1]) == 0)
		*words--;
	if (char_is_separator(str[iter->i]) == 1
		&& char_is_separator(str[iter->i + 1]) == 2)
		*words++;
}
