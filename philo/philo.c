/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:33:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/31 22:36:12 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_isvalid_arg(int argc, char *argv[]);

//static void	philo_sim_monitoring(t_philo *philo, t_data *data);

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
		//philo_sim_monitoring(philo, data);
		philo_philoclean(philo, data);
	}
	philo_dataclean(data);
	return (0);
}
/*
static void	philo_sim_monitoring(t_philo *philo, t_data *data)
{
	int					i;
	unsigned long int	time;

	while (data->sim)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			time = (philo_getinst() / 1000);
			if ((time - (philo + i)->t_life) >= data->t_die)
			{
				(philo + i)->stat = 1 << M_DIE;
				pthread_mutex_lock(data->s_mtx);
				data->sim = 0;
				pthread_mutex_unlock(data->s_mtx);
				break ;
			}
		}
	}
}
*/
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
			philo_stamperr("Error: Use just positive decimal number");
			return (0);
		}
	}
	return (1);
}
