/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inseption_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 10:52:41 by ereginia          #+#    #+#             */
/*   Updated: 2022/03/04 14:23:18 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_dollar(char *str)
{
    int i = 0;
    int flag = 0;

    while (str[i])
    {
        if (str[i] == '\'')
            flag = !flag;
        if (str[i] == '$' && !flag)
            return (1);
        i++;
    }
    return (0);
}
//////////////////////////////////////////////////////
static int dollar_len(t_minishell *m_shell, char *str, int *l)
{
    int i = 0;
    int k = 0;
    char *buf;

    
    while (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
        i++;
    *l = *l + i + 1;
    buf = ft_substr(str, 1, i);
    if (!ft_strncmp(buf, "?", 2))
    {
        k++;
        while (i / 10)
        {
            i = i / 10;
            k++;
        }
    }
    else
        k = ft_strlen(search_envs(&m_shell->envs, buf));
    free(buf);
    return (k);
}

static int word_len(t_minishell *m_shell, char *str)
{
    int i = 0;
    int k = 0;
    int flag = 0;

    while (str[i])
    {
		if (str[i] == '\'' && flag == 0)
		{
			flag = 1;
			k++;
			i++;
			continue ;
		}
		if (str[i] == '\"' && flag == 0)
		{
			flag = 2;
			k++;
			i++;
			continue ;
		}
		while (str[i] && flag)
		{
			if (str[i] == '\'' && flag == 1)
				flag = 3;
			if (str[i] == '\"' && flag == 2)
				flag = 3;
			if (str[i] == '$' && flag != 1)
			    k = k + dollar_len(m_shell, &str[i], &i);
			else
			{
			    k++;
			    i++;
			}
		}
		if (flag == 3)
		{
		    flag = 0;
		    continue ;
		}
		if (str[i] && !flag)
		{
		    if (str[i] == '$')
		        k = k + dollar_len(m_shell, &str[i], &i);
            else
            {
                k++;
		        i++;
            }
		}
    }
    return (k);
}
//////////////////////////////////////////////////////

static char *word_replace(t_minishell *m_shell, char *str)
{
    char    *res;
    char    *buf;
    char    *temp;
    int     i = 0;
    int     j = 0;
    int     k = 0;
    int     flag = 0;

    res = (char *)malloc(sizeof(char) * word_len(m_shell, str) + 1);
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
        if (str[i] != '$' || flag == 1)
            res[k] = str[i];
        else
        {
            while (str[i + j + 1] && (ft_isalnum(str[i + j + 1]) || str[i + j + 1] == '?'))
                j++;
            buf = ft_substr(&str[i], 1, j);
            if (!ft_strncmp(buf, "?", 2))
                temp = ft_itoa(m_shell->error_code);
            else
                temp = search_envs(&m_shell->envs, buf);
            ft_strlcpy(&res[k], temp, ft_strlen(temp) + 1);
            k = k + ft_strlen(temp);
            free(buf);
            i = i + j + 1;
            j = 0;
            continue ;
        }
        i++;
        k++;
    }
    res[k] = '\0';
    return res;
}

void split_inseption(t_minishell *m_shell, char **spt)
{
    int i = 0;
    char *buf;
    
    while (spt[i])
    {
        if (is_dollar(spt[i]))
        {
            buf = spt[i];
            spt[i] = word_replace(m_shell, buf);
            free(buf);
        }
        i++;
    }
}
