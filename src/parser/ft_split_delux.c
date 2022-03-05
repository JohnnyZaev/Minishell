/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:44:42 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 15:20:16 by ereginia         ###   ########.fr       */
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
		if (char_is_separator(str[iter.i + 1]) > 0
			&& char_is_separator(str[iter.i]) == 0)
			words++;
		if (char_is_separator(str[iter.i]) > 0
			&& char_is_separator(str[iter.i]) < 3 && !str[iter.i + 1])
			words++;
		if (char_is_separator(str[iter.i]) > 0
			&& char_is_separator(str[iter.i + 1]) == 0)
			words++;
		if (char_is_separator(str[iter.i]) == 2
			&& char_is_separator(str[iter.i + 1]) == 0)
			words--;
		if (char_is_separator(str[iter.i]) == 1
			&& char_is_separator(str[iter.i + 1]) == 2)
			words++;
		iter.i++;
	}
	return (words);
}

static void	write_word(char *dest, char *from, int size)
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
			while(char_is_separator(str[iter.i + iter.j]) == 1 && str[iter.i + iter.j] != '\0')
				iter.j++;
		}
		split[word] = (char*)malloc(sizeof(char) * (iter.j + 1));
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

// int main(int argc, char **argv)
// {
// 	int i = 0;
// 	char **spt;

// 	printf("%d\n", count_words(argv[1]));
// 	spt = ft_split_delux(str);
// 	while(spt[i])
// 	{
// 		printf("elem - %s\n", spt[i]);
// 		free(spt[i]);
// 		i++;
// 	}
// 	free(spt);
// }
