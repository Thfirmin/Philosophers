/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routineutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:16:50 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 12:13:08 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (!philo_islive(philo))
		return ;
	pthread_mutex_lock(philo->m_stat);
	if (!(philo->stat & (1 << M_FORK2)))
	{
		pthread_mutex_unlock(philo->m_stat);
		return ;
	}
	pthread_mutex_unlock(philo->m_stat);
	philo->t_life = (philo_getinst() / 1000);
	philo_stampmod(philo, M_EAT);
	philo_usleep(philo, philo->data->t_eat);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo_islive(philo))
		return ;
	pthread_mutex_lock(philo->m_stat);
	if (!(philo->stat & (1 << M_EAT)))
	{
		pthread_mutex_unlock(philo->m_stat);
		return ;
	}
	pthread_mutex_unlock(philo->m_stat);
	philo_stampmod(philo, M_SLEEP);
	philo_usleep(philo, philo->data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	if (!philo_islive(philo))
		return ;
	if ((philo->stat & (1 << M_SLEEP)))
		philo_stampmod(philo, M_THINK);
	philo_usleep(philo, philo->data->t_sleep);
}

int	philo_islive(t_philo *philo)
{
	pthread_mutex_lock(philo->data->s_mtx);
	if (!philo->data->sim)
	{
		pthread_mutex_unlock(philo->data->s_mtx);
		return (0);
	}
	pthread_mutex_unlock(philo->data->s_mtx);
	pthread_mutex_lock(philo->m_stat);
	if (philo->stat & (1 << M_DIE))
	{
		pthread_mutex_unlock(philo->m_stat);
		return (0);
	}
	pthread_mutex_unlock(philo->m_stat);
	return (1);
}

void	philo_usleep(t_philo *philo, unsigned long int time)
{
	unsigned long int	init;
	unsigned long int	inst;

	if (!philo_islive(philo))
		return ;
	init = (philo_getinst() / 1000);
	inst = init;
	while ((inst - init) < time)
	{
		inst = (philo_getinst() / 1000);
		if ((inst - philo->t_life) >= philo->data->t_die)
		{
			pthread_mutex_lock(philo->m_stat);
			philo->stat |= 1 << M_DIE;
			pthread_mutex_unlock(philo->m_stat);
			return ;
		}
	}
}
