/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:00:45 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/10 11:51:12 by ereginia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//создание массива пайпов
//(каждый пайп это int pipe[2] - массив из двух элементов)
int	**ft_piping(int count)
{
	int	i;
	int	**p_pipes;

	i = -1;
	if (count == 0)
		return (NULL);
	p_pipes = (int **)malloc(sizeof(int *) * (count + 1));
	if (p_pipes == NULL)
		return (NULL);
	while (i++ < count)
	{
		p_pipes[i] = malloc(sizeof(int) * 2);
		if (p_pipes[i] == NULL || pipe(p_pipes[i]) < 0)
		{
			ft_putstr_fd("pipe creation error\n", 2);
			while (i > 0)
			{
				free(p_pipes[i]);
				i--;
			}
			free(p_pipes);
			return (NULL);
		}
	}
	return (p_pipes);
}

//выделение места под массив PID
int	*ft_piding(int count)
{
	int	i;
	int	*p_pids;

	i = 0;
	p_pids = (int *)malloc(sizeof(int) * count);
	return (p_pids);
}

//перенаправляем вывод одной трубы на вывод другой трубы
void	pipe_welding(int *pipe1, int *pipe2)
{
	close(pipe1[1]);
	ft_dup(pipe1[0], 0);
	close(pipe1[0]);
	close(pipe2[0]);
	ft_dup(pipe2[1], 1);
	close(pipe2[1]);
}

