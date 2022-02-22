/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_pids.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:00:45 by ereginia          #+#    #+#             */
/*   Updated: 2022/02/21 12:06:17 by ereginia         ###   ########.fr       */
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

//закрываем неиспользуемые дескрипторы
void	close_unusedpipes(int **pipes, int pipe_num1, int pipe_num2, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if ((i != pipe_num1) && (i != pipe_num2))
		{
			close(pipes[i][0]);
			close(pipes[i][1]);
		}
		i++;
	}
}

//ждем смерти всех дочерних процессов
void	wait_all_pids(int pids_count)
{
	int	i;

	i = 0;
	while (i++ < pids_count)
		wait(NULL);
}
