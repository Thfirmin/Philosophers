/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_rdwr_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:34:55 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 18:39:59 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_rdph_stat(t_philo *ph, t_status flag)
{
	pthread_mutex_lock(ph->data->m_philo);
	if (ph->stat & (1 << flag))
	{
		pthread_mutex_unlock(ph->data->m_philo);
		return (1);
	}
	pthread_mutex_unlock(ph->data->m_philo);
	return (0);
}

void	ph_wrph_stat(t_philo *ph, t_status flag, short mod)
{
	pthread_mutex_lock(ph->data->m_philo);
	if (!mod)
		ph->stat = (1 << flag);
	else
	{
		ph->stat |= (1 << flag);
		if (mod < 0)
			ph->stat ^= (1 << flag);
	}
	pthread_mutex_unlock(ph->data->m_philo);
}

int	ph_rdph(t_philo *ph, void *data)
{
	int	ret;

	pthread_mutex_lock(ph->data->m_philo);
	ret = *(int *)data;
	pthread_mutex_unlock(ph->data->m_philo);
	return (ret);
}

void	ph_wrph(t_philo *ph, void *data, int aux, short mod)
{
	pthread_mutex_lock(ph->data->m_philo);
	if (!mod)
		*(int *)data = aux;
	else if (mod > 0)
		*(int *)data += aux;
	else
		*(int *)data -= aux;
	pthread_mutex_unlock(ph->data->m_philo);
}

time_t	ph_rdph_tlife(t_philo *ph)
{
	time_t	tlife;

	pthread_mutex_lock(ph->data->m_philo);
	tlife = ph->t_life;
	pthread_mutex_unlock(ph->data->m_philo);
	return (tlife);
}
