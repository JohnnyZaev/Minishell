/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:44:42 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 15:53:40 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';')
		return (1);
	if (c == ' ')
		return (2);
	if (c == '\0')
		return (3);
	return (0);
}

static int	count_words(char *str)
{
	int		words;
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	words = 0;
	while (str[iter.i])
	{
		set_half_flag(str, &iter);
		while (str[iter.i] && iter.flag)
		{
			iter.i++;
			if (str[iter.i] == '\'' && iter.flag == 1)
				iter.flag = !iter.flag;
			if (str[iter.i] == '\"' && iter.flag == 2)
				iter.flag = !iter.flag;
		}
		if (iter.flag)
			return (-1);
		count_words_helper(str, &iter, &words);
		iter.i++;
	}
	return (words);
}

static int	one_word(char *str)
{
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	while (str[iter.j] && char_is_separator(str[iter.j]) == 0)
	{
		set_half_flag(str, &iter);
		if (iter.flag)
		{
			while (str[iter.j] && iter.flag)
			{
				iter.j++;
				if ((str[iter.j] == '\'' && iter.flag == 1)
					|| (str[iter.j] == '\"' && iter.flag == 2))
					iter.flag = !iter.flag;
			}
			iter.j++;
			iter.flag = 0;
			continue ;
		}
		while (str[iter.j] && char_is_separator(str[iter.j]) == 0
			&& str[iter.j] != '\'' && str[iter.j] != '\"')
			iter.j++;
	}
	return (iter.j);
}

static void	write_split(char **split, char *str)
{
	int		word;
	t_stuff	iter;

	ft_memset(&iter, 0, sizeof(iter));
	word = 0;
	while (str[iter.i] != '\0')
	{
		iter.j = 0;
		while (char_is_separator(str[iter.i + iter.j]) == 2)
			iter.i++;
		if (!str[iter.i])
			return ;
		iter.j = one_word(&str[iter.i]);
		if (char_is_separator(str[iter.i + iter.j]) == 1 && iter.j == 0)
		{
			while (char_is_separator(str[iter.i + iter.j]) == 1 \
				&& str[iter.i + iter.j] != '\0')
				iter.j++;
		}
		split[word] = (char *)malloc(sizeof(char) * (iter.j + 1));
		write_word(split[word], str + iter.i, iter.j);
		iter.i += iter.j;
		word++;
	}
}

char	**ft_split_delux(char *str)
{
	char	**res;
	int		words;

	words = count_words(str);
	if (words < 0)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	write_split(res, str);
	res[words] = 0;
	return (res);
}
