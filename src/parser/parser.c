/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:00:48 by gvarys            #+#    #+#             */
/*   Updated: 2022/02/10 11:37:12 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	type_searcher(char *str)
{
	if (!(ft_strncmp(str, "|", 2)))
		return (PIPE);
	if (!(ft_strncmp(str, ";", 2)))
		return (BIN);
	return (0);
}

static t_str_exe	*create_str_exe(char *content)
{
	t_str_exe	*new;

	new = (t_str_exe *)ft_calloc(1, sizeof(t_str_exe));
	if (!new)
		return (new);
	new->str_exe = strdup(content);
	if (!new->str_exe)
	{
		free(new);
		new = NULL;
		return (new);
	}
	return (new);
}

static void	str_exe_addback(t_str_exe **str_exe, t_str_exe *new)
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

static void	parse_handler(t_minishell *m_shell, char **str)
{
	t_str_exe	*temp;
	int			i;

	temp = NULL;
	i = -1;
	while (str[++i])
	{
		if (type_searcher(str[i]))
		{
			if (temp)
				temp->type = type_searcher(str[i]);
			else
				exit(EXIT_FAILURE);
			continue ;
		}
		temp = create_str_exe(str[i]);
		if (temp == NULL)
			exit(error(1));
		if (i == 0)
			m_shell->str_exe = temp;
		else
			str_exe_addback(&m_shell->str_exe, temp);
	}
}

void	parse_str(t_minishell *m_shell, char *str)
{
	char	**str_split;

	str = ft_strtrim(str, " \t");
	if (!str)
		exit(error(2));
	if (ft_strlen(str) == 0)
		return ;
	str_split = ft_split(str, ' ');
	if (!str_split)
		exit(error(2));
	parse_handler(m_shell, str_split);
}
