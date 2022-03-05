/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_delux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:44:42 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 11:01:49 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		char_is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == ';')
		return (1);
	if (c == ' ')
		return (2);
	if (c == '\0')
		return (3);
	return (0);
}

static int		count_words(char *str)
{
	int	i;
	int flag;
	int	words;

	words = 0;
	flag = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			flag = 1;
		if (str[i] == '\"')
			flag = 2;
		while (str[i] && flag)
		{
			i++;
			if (str[i] == '\'' && flag == 1)
				flag = !flag;
			if (str[i] == '\"' && flag == 2)
				flag = !flag;
		}
		if (flag)
			return -1;
		if (char_is_separator(str[i + 1]) > 0
				&& char_is_separator(str[i]) == 0)
			words++;
		if (char_is_separator(str[i]) > 0
				&& char_is_separator(str[i]) < 3 && !str[i + 1])
			words++;
		if (char_is_separator(str[i]) > 0
				&& char_is_separator(str[i + 1]) == 0)
			words++;
		if (char_is_separator(str[i]) == 2
				&& char_is_separator(str[i + 1]) == 0)
			words--;
		if (char_is_separator(str[i]) == 1
				&& char_is_separator(str[i + 1]) == 2)
			words++;
		i++;
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

static int one_word(char *str)
{
	int j;
	int flag;

	j = 0;
	flag = 0;
	while (str[j] && char_is_separator(str[j]) == 0)
	{
		if (str[j] == '\'')
			flag = 1;
		if (str[j] == '\"')
			flag = 2;
		if (flag)
		{
			while (str[j] && flag)
			{
				j++;
				if (str[j] == '\'' && flag == 1)
					flag = !flag;
				if (str[j] == '\"' && flag == 2)
					flag = !flag;
			}
			j++;
			flag = 0;
			continue ;
		}
		while (str[j] && char_is_separator(str[j]) == 0 && str[j] != '\'' && str[j] != '\"')
			j++;
	}
	return (j);
}

static void	write_split(char **split, char *str)
{
	int		i;
	int		j;
	int		word;
	int		flag;

	word = 0;
	flag = 0;
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (char_is_separator(str[i + j]) == 2)
			i++;
		if (!str[i])
			return ;
		j = one_word(&str[i]);
		if (char_is_separator(str[i + j]) == 1 && j == 0)
		{
			while(char_is_separator(str[i + j]) == 1 && str[i + j] != '\0')
				j++;
		}
		split[word] = (char*)malloc(sizeof(char) * (j + 1));
		write_word(split[word], str + i, j);
		i += j;
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
	res = (char**)malloc(sizeof(char*) * (words + 1));
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