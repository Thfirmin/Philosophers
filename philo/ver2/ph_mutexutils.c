/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutexutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:56 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/10 21:14:09 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

mutex_t	*ph_initmutex(void)
{
	mutex_t	*mtx;

	mtx = malloc(sizeof(mutex_t));
	if (mtx)
	{
		memset(mtx, 0, sizeof(mutex_t));
		if (pthread_mutex_init(mtx, 0) != 0)
		{
			free(mtx);
			mtx = (void *)0;
		}
	}
	return (mtx);
}

mutex_t	**ph_initfork(t_data *data)
{
	mutex_t	**fork;
	int		i;

	fork = malloc(data->n_philo * sizeof(mutex_t *));
	if (fork)
	{
		memset(fork, 0, (data->n_philo * sizeof(mutex_t *)));
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

void	ph_destroymutex(mutex_t **mtx)
{
	if (!*mtx)
		return ;
	pthread_mutex_destroy(*mtx);
	free(*mtx);
	*mtx = 0;
}

void	ph_destroyfork(t_data *data, mutex_t ***fork)
{
	int	i;

	if (!*fork)
		return ;
	i = -1;
	while (++i < data->n_philo)
		ph_destroymutex((*fork + i));
	free(*fork);
}
