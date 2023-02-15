/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_philoutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:07 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 13:47:31 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ph_initphilo(t_data *data)
{
	int		i;
	t_philo	*philo;

	philo = malloc(data->n_philo * sizeof(t_philo));
	if (philo)
	{
		memset(philo, 0, (data->n_philo * sizeof(t_philo)));
		i = -1;
		data->start = ph_getinst(0);
		while (++i < data->n_philo)
		{
			(philo + i)->nb = (i + 1);
			(philo + i)->data = data;
			(philo + i)->n_eat = 0;
			(philo + i)->stat = (1 << P_THINK);
			(philo + i)->t_life = data->start;
			if (pthread_create(&(philo + i)->id, 0, ph_routine, (philo + i)))
				break ;
		}
		if (i != data->n_philo)
		{
			pthread_mutex_lock(data->m_data);
			data->sim = 0;
			pthread_mutex_unlock(data->m_data);
		}
	}
	return (philo);
}

int	ph_checkphilo(t_philo *philo, t_data *data)
{
	int	i;

	if (!philo)
	{
		ph_stamperr("Error: Philo allocation failed\n");
		return (0);
	}
	i = -1;
	while (++i < data->n_philo)
	{
		if (!(philo + i)->id)
		{
			ph_stamperr("Error: Philo initialization failded\n");
			ph_cleanphilo(&philo, data);
			return (0);
		}
	}
	return (1);
}

void	ph_cleanphilo(t_philo **philo, t_data *data)
{
	int	i;

	if (!*philo)
		return ;
	i = -1;
	while (++i < data->n_philo)
		pthread_join((*philo + i)->id, 0);
	free(*philo);
	*philo = 0;
}
