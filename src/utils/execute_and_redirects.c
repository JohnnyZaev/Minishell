/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:26:23 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/10 11:41:23 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//запускает бинарник
void    execute_process(char *c_line, char **envp)
{
    char	**argVec1;

	argVec1 = ft_split(c_line, ' ');
	execve(ft_exist(envp, argVec1[0]), argVec1, NULL);
    exit(EXIT_SUCCESS);
}

//открывает файл и перенаправляет в stdin
void    read_redirect(int fd_out, char *file_path)
{
    int fd_in;

    fd_in = open(file_path, O_RDONLY);
    ft_dup(fd_out, 1);
    ft_dup(fd_in, 0);
}

//открывает/создает файл и перенаправляет stdout в файл
void    write_redirect(int fd_in, char *file_path)
{
    int fd_out;

    fd_out = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    ft_dup(fd_out, 1);
    ft_dup(fd_in, 0);
}

//heredoc
void	read_heredoc_process(char *stop, int fd)
{
	int		readed;
    int     len;
	char	*buf;

	readed = 1;
    len = ft_strlen(stop);
    buf = (char *)malloc(len);
	while (readed)
	{
        write(1, "heredoc>", 9);
		readed = read(0, &buf, 10);
		if (!ft_strncmp(buf, stop, len))
			exit(EXIT_SUCCESS);
		write(fd, &buf, readed);
	}
    free(buf);
}