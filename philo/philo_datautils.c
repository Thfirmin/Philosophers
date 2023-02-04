/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_datautils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 00:20:49 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 23:46:39 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static pthread_mutex_t	*philo_datainit_fork(t_data *data);

t_data	*philo_datainit(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (data);
	memset(data, 0, sizeof(t_data));
	data->n_philo = philo_atol(argv[1]);
	data->t_die = (philo_atol(argv[2]) * 1000);
	data->t_eat = (philo_atol(argv[3]) * 1000);
	data->t_sleep = (philo_atol(argv[4]) * 1000);
	data->n_eat = -1;
	data->sim = 1;
	if (argc == 6)
		data->n_eat = philo_atol(argv[5]);
	data->fork = philo_datainit_fork(data);
	data->s_mtx = philo_mtxinit();
	return (data);
}

int	philo_datacheck(t_data *data)
{
	if (!data)
	{
		philo_stamperr("Error: Problem to allocate data struct\n");
		return (0);
	}
	if (!data->fork || !data->s_mtx)
	{
		philo_stamperr("Error: Problem to allocate mutexes\n");
		philo_dataclean(data);
		return (0);
	}
	return (1);
}

void	philo_dataclean(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	if (data->s_mtx)
	{
		pthread_mutex_destroy(data->s_mtx);
		free(data->s_mtx);
	}
	if (data->fork)
	{
		while (++i < data->n_philo)
			pthread_mutex_destroy(data->fork + i);
		free(data->fork);
	}
	free(data);
}

static pthread_mutex_t	*philo_datainit_fork(t_data *data)
{
	pthread_mutex_t	*fork;
	int				i;

	fork = malloc(data->n_philo * sizeof(pthread_mutex_t));
	if (!fork)
		return (0);
	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_mutex_init((fork + i), 0))
			break ;
	}
	if (i != data->n_philo)
	{
		while (--i > -1)
			pthread_mutex_destroy(fork + i);
		free(fork);
		fork = 0;
	}
	return (fork);
}
