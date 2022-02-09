/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:38:24 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/09 12:50:45 by gvarys           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//проверяет существует ли такой бинарник
//если существует то возвращает строку = полный путь
//если не существует то возвращает NULL
char	*ft_exist(char **envp, char *cmd)
{
	char	**path;
	char	*buf;
	char	*buf2;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) && envp[i] != NULL)
		i++;
	path = ft_split(envp[i] + 5, ':');
	i = 0;
	while (path[i] != NULL)
	{
		buf = ft_strjoin(path[i], "/");
		buf2 = ft_strjoin(buf, cmd);
		free(buf);
		if (!access(buf2, 0))
		{
			free(path);
			return (buf2);
		}
		free(buf2);
		i++;
	}
	free(path);
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
