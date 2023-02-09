/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:33:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/08 22:16:28 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_isvalid_arg(int argc, char *argv[]);

static int	simas(t_data *data);

static void	philo_sim_monitoring(t_philo *philo, t_data *data);

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philo;

	if (!philo_isvalid_arg(argc, argv))
		return (2);
	data = philo_datainit(argc, argv);
	if (!philo_datacheck(data))
		return (2);
	if (data->t_die && data->n_philo)
	{
		philo = philo_philoinit(data);
		if (!philo_philocheck(philo))
			return (2);
		philo_sim_monitoring(philo, data);
		philo_philoclean(philo, data);
	}
	philo_dataclean(data);
	return (0);
}

static void	philo_sim_monitoring(t_philo *philo, t_data *data)
{
	int					i;
	unsigned long int	time;

	usleep(200);
	while (simas(data))
	{
		i = -1;
		while (++i < data->n_philo)
		{
			pthread_mutex_lock((philo + i)->data->s_mtx);
			time = ((philo_getinst() - (philo + i)->t_life) >= data->t_die);
			pthread_mutex_unlock((philo + i)->data->s_mtx);
			if (time)
			{
				pthread_mutex_lock((philo + i)->data->s_mtx);
				data->sim = 0;
				pthread_mutex_unlock((philo + i)->data->s_mtx);
				pthread_mutex_lock((philo + i)->m_stat);
				philo->stat |= (1 << M_DIE);
				pthread_mutex_unlock((philo + i)->m_stat);
				break ;
			}
			usleep(150);
		}
	}
}

static int	simas(t_data *data)
{
	pthread_mutex_lock(data->s_mtx);
	if (data->sim)
	{
		pthread_mutex_unlock(data->s_mtx);
		return (1);
	}
	pthread_mutex_unlock(data->s_mtx);
	return (0);
}

static int	philo_isvalid_arg(int argc, char *argv[])
{
	int		i;

	if ((argc < 5) || (argc > 6))
	{
		philo_stamperr(0);
		return (0);
	}
	i = 0;
	while (*(argv + ++i))
	{
		if (!philo_isposnumber(*(argv + i)))
		{
			philo_stamperr("Error: Use just positive decimal number\n");
			return (0);
		}
	}
	return (1);
}

pthread_mutex_t	*philo_mtxinit(void)
{
	pthread_mutex_t	*mtx;

	mtx = malloc(sizeof(pthread_mutex_t));
	if (!mtx)
		return (0);
	if (pthread_mutex_init(mtx, 0))
	{
		free(mtx);
		mtx = 0;
	}
	return (mtx);
}
