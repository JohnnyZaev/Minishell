/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comma_killer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 11:20:45 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/05 15:13:56 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char *str)
{
	int	i;
	int	flag;
	int	word;

	i = 0;
	flag = 0;
	word = 1;
	while (str[i])
	{
		if (str[i] == '\'' && flag == 0)
			flag = 1;
		else if (str[i] == '\'' && flag == 1)
			flag = 0;
		if (str[i] == '\"' && flag == 0)
			flag = 2;
		else if (str[i] == '\"' && flag == 2)
			flag = 0;
		if (str[i] == ' ' && str[i + 1] != ' ' && !flag)
			word++;
		i++;
	}
	return (word);
}

static int	char_count(char *str, int *i)
{
	int	j;
	int	k;
	int	flag;

	j = 0;
	k = *i;
	flag = 0;
	while (str[*i])
	{
		if (str[*i] == '\'' && flag == 0)
		{
			j++;
			flag = 1;
		}
		else if (str[*i] == '\'' && flag == 1)
			flag = 0;
		if (str[*i] == '\"' && flag == 0)
		{
			j++;
			flag = 2;
		}
		else if (str[*i] == '\"' && flag == 2)
			flag = 0;
		if (str[*i] == ' ' && !flag)
			break ;
		*i = *i + 1;
	}
	j = *i - 2 * j - k;
	return (j);
}

static void	write_word(char *dest, char *from, int size)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (from[i] && j < size)
	{
		if (from[i] == '\'' && flag == 0)
			flag = 1;
		else if (from[i] == '\'' && flag == 1)
			flag = 0;
		if (from[i] == '\"' && flag == 0)
			flag = 2;
		else if (from[i] == '\"' && flag == 2)
			flag = 0;
		if ((from[i] == '\'' && flag != 2) || (from[i] == '\"' && flag != 1))
		{
			i++;
			continue ;
		}
		dest[j] = from[i];
		i++;
		j++;
	}
	dest[j] = '\0';
}

static void	write_split(char **split, char *str)
{
	int		i;
	int		j;
	int		k;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		k = i;
		j = char_count(str, &i);
		split[word] = (char *)malloc(sizeof(char) * (j + 1));
		write_word(split[word], str + k, j);
		if (str[i] == ' ')
			i++;
		word++;
	}
	split[word] = NULL;
}

char	**comma_killer(char *str)
{
	char	**res;
	int		words;
	int		i;

	i = 0;
	words = count_words(str);
	if (words < 0)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	write_split(res, str);
	return (res);
}
