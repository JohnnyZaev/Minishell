/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:38:24 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/22 15:21:00 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//проверяет существует ли такой бинарник
//если существует то возвращает строку = полный путь
//если не существует то возвращает NULL
char	*ft_exist(char *env, char *cmd)
{
	char	**path;
	char	*buf;
	char	*buf2;
	int		i;

	i = 0;
	path = ft_split(env, ':');
	i = 0;
	while (path[i] != NULL)
	{
		buf = ft_strjoin(path[i], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (!access(buf2, 0))
		{
			free_split(path);
			return (buf2);
		}
		free(buf2);
		i++;
	}
	free_split(path);
	return (NULL);
}

//простой вызов dup2 обернутый обработкой ошибок
int	ft_dup(int old, int newfd)
{
	int	buf;

	buf = dup2(old, newfd);
	if (buf == -1)
	{
		ft_putstr_fd("dup2 error\n", 2);
		exit(EXIT_FAILURE);
	}
	return (buf);
}

//простой вызов fork обернутый обработкой ошибок
int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("fork failed\n", 2);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

//простой вызов pipe обернутый обработкой ошибок
void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_putstr_fd("pipe creation failed\n", 2);
		exit(EXIT_FAILURE);
	}
}
