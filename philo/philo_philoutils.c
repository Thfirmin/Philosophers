/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_philoutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 01:32:55 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 17:47:00 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_philo	*philo_philoinit(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(data->n_philo * sizeof(t_philo));
	if (!philo)
		return (philo);
	memset(philo, 0, (data->n_philo * sizeof(t_philo)));
	i = -1;
	data->instant = philo_getinst();
	while (++i < data->n_philo)
	{
		(philo + i)->nb = (i + 1);
		(philo + i)->data = data;
		(philo + i)->stat = 1 << M_THINK;
		(philo + i)->m_stat = philo_mtxinit();
		if (!(philo + i)->m_stat)
			break ;
		(philo + i)->t_life = philo_getinst();
		if (pthread_create(&(philo + i)->id, 0, philo_routine, (philo + i)))
			break ;
	}
	if (i != data->n_philo)
		philo_write(&data->sim, 0, data->s_mtx);
	return (philo);
}

int	philo_philocheck(t_philo *philo)
{
	if (!philo)
	{
		philo_stamperr("Error: Problem to alloc philo struct\n");
		return (0);
	}
	return (1);
}


void	philo_philoclean(t_philo *philo, t_data *data)
{
	int	i;

	if (!philo)
		return ;
	i = -1;
	while (++i < data->n_philo)
		pthread_join((philo + i)->id, 0);
	free(philo);
}

