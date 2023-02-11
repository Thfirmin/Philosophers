/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:19 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/11 08:57:27 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_routine(void *param)
{
	t_philo	*philo;
	
	philo = param;
	while (ph_islive(philo))
	{
		ph_takeone_fork(philo);
		ph_taketwo_fork(philo);
		ph_eat(philo);
		ph_dropfork(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	ph_die(philo);
	return (0);
}

void	ph_eat(t_philo *ph)
{
	unsigned char	stat;
	
	if (!ph_islive(ph))
		return ;
	pthread_mutex_lock(ph->data->m_philo);
	stat = ph->stat;
	pthread_mutex_unlock(ph->data->m_philo);
	if (!(stat & (1 << P_FORK2)))
		return ;
	ph_stampmod(ph, P_EAT);
	pthread_mutex_lock(ph->data->m_philo);
	ph->t_life = ph_getinst(0);
	ph->n_eat++;
	if (ph->n_eat == ph->data->n_eat)
	{
		pthread_mutex_unlock(ph->data->m_philo);
		pthread_mutex_lock(ph->data->m_data);
		ph->data->sim = 0;
		pthread_mutex_unlock(ph->data->m_data);
		return ;
	}
	pthread_mutex_unlock(ph->data->m_philo);
	ph_usleep(ph, ph->data->t_eat);
}

void	ph_sleep(t_philo *ph)
{
	unsigned char	stat;

	if (!ph_islive(ph))
		return ;
	pthread_mutex_lock(ph->data->m_philo);
	stat = ph->stat;
	pthread_mutex_unlock(ph->data->m_philo);
	if (!(stat & (1 << P_EAT)))
		return ;
	ph_stampmod(ph, P_SLEEP);
	ph_usleep(ph, ph->data->t_sleep);
}

void	ph_think(t_philo *ph)
{
	unsigned char	stat;

	if (!ph_islive(ph))
		return ;
	pthread_mutex_lock(ph->data->m_philo);
	stat =  ph->stat;
	pthread_mutex_unlock(ph->data->m_philo);
	if ((stat & (1 << P_SLEEP)))
		ph_stampmod(ph, P_THINK);
	ph_usleep(ph, T_THINK);
}

void	ph_die(t_philo *ph)
{
	pthread_mutex_lock(ph->data->m_data);
	if (ph->data->unic)
	{
		pthread_mutex_unlock(ph->data->m_data);
		return ;
	}
	else
		ph->data->unic ++;
	pthread_mutex_unlock(ph->data->m_data);
	pthread_mutex_lock(ph->data->m_philo);
	if (!(ph->stat & (1 << P_DIE)))
	{
		pthread_mutex_unlock(ph->data->m_philo);
		return ;
	}
	pthread_mutex_unlock(ph->data->m_philo);
	ph_stampmod(ph, P_DIE);
}
