/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_max.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 13:07:17 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/10 17:23:25 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int		char_is_separator(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

static int		count_words(char *str, char *charset)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (char_is_separator(str[i + 1], charset) == 1
				&& char_is_separator(str[i], charset) == 0)
			words++;
		if (char_is_separator(str[i], charset) == 1
				&& char_is_separator(str[i + 1], charset) == 0)
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dest, char *from, char *charset)
{
	int	i;

	i = 0;
	if (char_is_separator(from[0], charset) == 1)
	{
	    while (char_is_separator(from[i], charset) == 1)
		{
	        dest[i] = from[i];
			i++;
		}
	    dest[i] = '\0';
	    return ;
	}
	while (char_is_separator(from[i], charset) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static void	write_split(char **split, char *str, char *charset)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (char_is_separator(str[i + j], charset) == 0)
			j++;
		if (char_is_separator(str[i + j], charset) == 1 && j == 0)
		{
			while(char_is_separator(str[i + j], charset) == 1)
				j++;
		}
		split[word] = (char*)malloc(sizeof(char) * (j + 1));
		write_word(split[word], str + i, charset);
		i += j;
		word++;
	}
}

char	**ft_split_max(char *str, char *charset)
{
	char	**res;
	int		words;

	words = count_words(str, charset);
	res = (char**)malloc(sizeof(char*) * (words + 1));
	res[words] = 0;
	write_split(res, str, charset);
	return (res);
}

// int main()
// {
// 	int i = 0;
// 	char **spt;
// 	char str[] = "grep j | wc -l >> toto.txt";

// 	spt = ft_split_max(str, "<|;");
// 	while(spt[i])
// 	{
// 		printf("elem - %s\n", spt[i]);
// 		i++;
// 	}
// }