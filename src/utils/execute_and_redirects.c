/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and_redirects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:26:23 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/23 14:36:16 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//запускает бинарник
void	execute_process(char *c_line, t_minishell *m_shell)
{
	char	**arg_vec1;
	char	**env;
	char	*bin_name;

	arg_vec1 = ft_split(c_line, ' ');
	env = get_envp(m_shell->envs);
	if (!access(arg_vec1[0], 0))
	{
		execve(arg_vec1[0], arg_vec1, env);
		free_split(arg_vec1);
		exit(EXIT_FAILURE);
	}
	bin_name = ft_exist(search_envs(&m_shell->envs, "PATH"), arg_vec1[0]);
	if (!bin_name)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(arg_vec1[0], 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	execve(bin_name, arg_vec1, env);
	free(bin_name);
	free_split(arg_vec1);
	exit(EXIT_SUCCESS);
}

//открывает файл и перенаправляет в stdin
void	read_redirect(char *file_path)
{
	int	fd_in;

	fd_in = open(file_path, O_RDONLY);
	if (fd_in < 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	ft_dup(fd_in, 0);
}

//открывает/создает файл и перенаправляет stdout в файл
void	write_redirect(char *file_path, int mode)
{
	int	fd_out;

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
	int		len;
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
