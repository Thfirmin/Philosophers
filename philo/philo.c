/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:33:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 23:52:20 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_isvalid_arg(int argc, char *argv[]);

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
	if (data->t_die)
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

	while (data->sim)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			time = philo_getinst();
			if ((time - (philo + i)->t_life) >= data->t_die)
			{
				philo_write(&philo->stat, (philo->stat | (1 << M_DIE)),
					philo->m_stat);
				philo_write(&data->sim, 0, data->s_mtx);
				break ;
			}
			usleep(150);
		}
	}
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
