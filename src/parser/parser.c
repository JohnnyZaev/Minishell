/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:00:48 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/16 12:49:06 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	type_searcher(char *str)
{
    if (!str)
        return (0);
	if (!(ft_strncmp(str, "|", 2)))
		return (PIPE);
	if (!(ft_strncmp(str, ";", 2)))
		return (BIN);
	if (!(ft_strncmp(str, "<", 2)))
		return (REDIRECT_IN);
	else if (!(ft_strncmp(str, "<<", 3)))
		return (HEREDOC);
	if (!(ft_strncmp(str, ">", 2)))
		return (REDIRECT_OUT);
	else if (!(ft_strncmp(str, ">>", 3)))
		return (REDIRECT_AP);
	return (0);
}

t_str_exe	*create_str_exe(char *content)
{
	t_str_exe	*new;

	new = (t_str_exe *)ft_calloc(1, sizeof(t_str_exe));
	if (!new)
		return (new);
	new->str_exe = ft_strdup(content);
	if (!new->str_exe)
	{
		free(new);
		new = NULL;
		return (new);
	}
	return (new);
}

void	str_exe_addback(t_str_exe **str_exe, t_str_exe *new)
{
	t_str_exe	*temp;
	t_str_exe	*save;

	save = *str_exe;
	if (!save)
		save = new;
	else
	{
		while (save->next)
			save = save->next;
		temp = save;
		save->next = new;
		temp = save->next;
		temp->prev = save;
	}
}

void	parse_str(t_minishell *m_shell, char *str)
{
	char	**str_split;
	char	*str_temp;
	int		i;

	str_temp = ft_strtrim(str, " \t");
	if (!str_temp)
		exit(1);
	if (ft_strlen(str_temp) == 0)
		return ;
	str_split = ft_split_max(str, "><|;", ' ');
	if (!str_split)
		exit(1);
	free(str_temp);
	parse_handler(m_shell, str_split);
	i = -1;
	while(str_split[++i])
	{
		str_temp = str_split[i];
		free(str_temp);
	}
	free(str_split);
}

void	free_str_exe(t_str_exe *str_exe)
{
	t_str_exe *temp;

	while (str_exe)
	{
		temp = str_exe;
		str_exe = str_exe->next;
		if (temp->str_exe)
			free(temp->str_exe);
		if (temp)
			free(temp);
	}
}