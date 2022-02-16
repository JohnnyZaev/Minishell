/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:26:23 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/16 16:34:50 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//запускает бинарник
void    execute_process(char *c_line, char **envp)
{
    char	**argVec1;
    char    *bin_name;

	argVec1 = ft_split(c_line, ' ');
    if (!access(argVec1[0], 0))
    {
        execve(argVec1[0], argVec1, NULL);
        free_split(argVec1);
        exit(EXIT_FAILURE);
    }
    bin_name = ft_exist(envp, argVec1[0]);
    execve(bin_name, argVec1, NULL);
    free(bin_name);
    free_split(argVec1);
    exit(EXIT_SUCCESS);
}

//открывает файл и перенаправляет в stdin
void    read_redirect(char *file_path)
{
    int fd_in;

    fd_in = open(file_path, O_RDONLY);
    ft_dup(fd_in, 0);
}

//открывает/создает файл и перенаправляет stdout в файл
void    write_redirect(char *file_path, int mode)
{
    int fd_out;

    if (mode == 4)
        fd_out = open(file_path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else if (mode == 6)
        fd_out = open(file_path, O_CREAT | O_WRONLY | O_APPEND, 0644);
    else
        return ;
    ft_dup(fd_out, 1);
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
	while (1)
	{
        write(1, "> ", 2);
		readed = read(0, &buf, len);
		if (!ft_strncmp(buf, stop, len) || readed > 0)
			break ;
		write(fd, &buf, readed);
	}
    free(buf);
}