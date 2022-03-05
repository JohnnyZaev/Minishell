/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:07:17 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 14:09:34 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	char_is_separator(char c, char *charset, char separator)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == separator)
		return (2);
	if (c == '\0')
		return (3);
	return (0);
}

static int	count_words(char *str, char *charset, char sep)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i + 1], charset, sep) > 0 \
			&& char_is_separator(str[i], charset, sep) == 0)
			words++;
		if (char_is_separator(str[i], charset, sep) > 0 \
			&& char_is_separator(str[i], charset, sep) < 3 && !str[i + 1])
			words++;
		if (char_is_separator(str[i], charset, sep) > 0 \
				&& char_is_separator(str[i + 1], charset, sep) == 0)
			words++;
		if (char_is_separator(str[i], charset, sep) == 2 \
				&& char_is_separator(str[i + 1], charset, sep) == 0)
			words--;
		if (char_is_separator(str[i], charset, sep) == 1 \
				&& char_is_separator(str[i + 1], charset, sep) == 2)
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dest, char *from, char *charset, char sep)
{
	int	i;

	i = 0;
	if (char_is_separator(from[0], charset, sep) == 1)
	{
		while (char_is_separator(from[i], charset, sep) == 1)
		{
			dest[i] = from[i];
			i++;
		}
		dest[i] = '\0';
		return ;
	}
	while (char_is_separator(from[i], charset, sep) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static void	write_split(char **split, char *str, char *charset, char sep)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (char_is_separator(str[i + j], charset, sep) == 2)
			i++;
		if (!str[i])
			return ;
		while (char_is_separator(str[i + j], charset, sep) == 0)
			j++;
		if (char_is_separator(str[i + j], charset, sep) == 1 && j == 0)
			while (char_is_separator(str[i + j], \
				charset, sep) == 1 && str[i + j] != '\0')
				j++;
		split[word] = (char *)malloc(sizeof(char) * (j + 1));
		write_word(split[word], str + i, charset, sep);
		i += j;
		word++;
	}
}

char	**ft_split_max(char *str, char *charset, char sep)
{
	char	**res;
	int		words;

	words = count_words(str, charset, sep);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	write_split(res, str, charset, sep);
	res[words] = 0;
	return (res);
}
