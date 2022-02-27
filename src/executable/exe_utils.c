/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 13:25:13 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/27 12:40:40 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//количество процессов нужно запустить
int pids_counter(t_minishell *m_shell)
{
	t_str_exe	*buf;
	int			pids;

	pids = 1;
	buf = m_shell->str_exe;
	while (buf)
	{
		if (buf->type == 1 || buf->type == 2 || buf->type == 5)
			pids++;
		buf = buf->next;
	}
	if (buf == m_shell->str_exe)
		return 0;
	return pids;
}

//количество пайп нужно проложить
int pipes_counter(t_minishell *m_shell)
{
	t_str_exe	*buf;
	int			pipes;

	pipes = 0;
	buf = m_shell->str_exe;
	while(buf)
	{
		if (buf->type == 1 || buf->type == 5)
			pipes++;
		buf = buf->next;
	}
	return pipes;
}

//возвращает лист после пайпы 
t_str_exe   *get_next_pipe(t_str_exe *str_exec)
{
	while (str_exec && str_exec->type > 2 && str_exec->type != 5)
		str_exec = (str_exec)->next;
	return (str_exec->next);
}

//если пайпа сзади то 1
//если пайпа спереди то 2
//если пайпа с обеих сторон то 3
int pipe_type(t_str_exe *str_exec)
{
	int			i;
	int			j;
	t_str_exe	*buf;

	buf = str_exec;
	if (buf->prev)
		i = (buf->prev->type == 1 || buf->prev->type == 5);
	else
		i = 0;
	while (buf && buf->type > 2 && str_exec->type != 5)
		buf = buf->next;
	j = (buf->type == 1 || buf->type == 5);
	return (i + 2 * j);
}

//номер пайпы сзади
int	which_pipe(t_str_exe *str_exec)
{
	t_str_exe	*buf;
	int			count;

	count = 0;
	buf = str_exec;
	while (buf)
	{
		if (buf->prev && (buf->prev->type == 1 || buf->prev->type == 5))
			count++;
		buf = buf->prev;
	}
	return (count);
}

char	**get_envp(t_envs *envs)
{
	char	**result;
	char	*temp;
	t_envs	*buf;
	int		words;

	words = 0;
	buf = envs;
	while (buf)
	{
		buf = buf->next;
		words++;
	}
	result = (char **)malloc(sizeof(char *) * (words + 1));
	words = 0;
	buf = envs;
	while (buf)
	{
		temp =  ft_strjoin(buf->key, "=");
		result[words] = ft_strjoin(temp, buf->value);
		free(temp);
		buf = buf->next;
		words++;
	}
	result[words] = NULL;
	return (result);
}