/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:56 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 20:28:10 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_mutex	*ph_initmutex(void)
{
	t_mutex	*mtx;

	mtx = malloc(sizeof(t_mutex));
	if (mtx)
	{
		memset(mtx, 0, sizeof(t_mutex));
		if (pthread_mutex_init(mtx, 0) != 0)
		{
			free(mtx);
			mtx = (void *)0;
		}
	}
	return (mtx);
}

t_mutex	**ph_initfork(t_data *data)
{
	t_mutex	**fork;
	int		i;

	fork = malloc(data->n_philo * sizeof(t_mutex *));
	if (fork)
	{
		memset(fork, 0, (data->n_philo * sizeof(t_mutex *)));
		i = -1;
		while (++i < data->n_philo)
		{
			*(fork + i) = ph_initmutex();
			if (!*(fork + i))
				break ;
		}
	}
	return (fork);
}

void	ph_destroymutex(t_mutex **mtx)
{
	if (!*mtx)
		return ;
	pthread_mutex_destroy(*mtx);
	free(*mtx);
	*mtx = 0;
}

void	ph_destroyfork(t_data *data, t_mutex ***fork)
{
	int	i;

	if (!*fork)
		return ;
	i = -1;
	while (++i < data->n_philo)
		ph_destroymutex((*fork + i));
	free(*fork);
}
