/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:15:35 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 11:56:31 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = param;
	while (philo_islive(philo))
	{
		philo_takeone_fork(philo);
		philo_taketwo_fork(philo);
		philo_eat(philo);
		philo_drop_fork(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	if (philo->stat & (1 << M_DIE))
		philo_die(philo);
	return (0);
}

void	philo_takeone_fork(t_philo *philo)
{
	int					p_nbr;

	if (!philo_islive(philo))
		return ;
	pthread_mutex_lock(philo->m_stat);
	if (!(philo->stat & (1 << M_THINK)))
	{
		pthread_mutex_unlock(philo->m_stat);
		return ;
	}
	pthread_mutex_unlock(philo->m_stat);
	p_nbr = philo->data->n_philo;
	if (philo->nb % 2)
		pthread_mutex_lock(&philo->data->fork[philo->nb % p_nbr]);
	else
		pthread_mutex_lock(&philo->data->fork[philo->nb - 1]);
	philo_stampmod(philo, M_FORK1);
}

void	philo_taketwo_fork(t_philo *philo)
{
	int					p_nbr;

	if (!philo_islive(philo))
		return ;
	pthread_mutex_lock(philo->m_stat);
	if (!((philo->stat & (1 << M_FORK1)) && (philo->data->n_philo >= 2)))
	{
		pthread_mutex_unlock(philo->m_stat);
		return ;
	}
	pthread_mutex_unlock(philo->m_stat);
	p_nbr = philo->data->n_philo;
	if (philo->nb % 2)
		pthread_mutex_lock(&philo->data->fork[philo->nb - 1]);
	else
		pthread_mutex_lock(&philo->data->fork[philo->nb % p_nbr]);
	philo_stampmod(philo, M_FORK2);
}

void	philo_drop_fork(t_philo *philo)
{
	int					p_nbr;

	pthread_mutex_lock(philo->m_stat);
	if (!(philo->stat & (1 << M_EAT)))
	{
		pthread_mutex_unlock(philo->m_stat);
		return ;
	}
	pthread_mutex_unlock(philo->m_stat);
	p_nbr = philo->data->n_philo;
	pthread_mutex_unlock(&philo->data->fork[philo->nb % p_nbr]);
	pthread_mutex_unlock(&philo->data->fork[philo->nb - 1]);
}

void	philo_die(t_philo *philo)
{
	pthread_mutex_lock(philo->data->s_mtx);
	if (!philo->data->unic)
		philo->data->unic = 1;
	else
	{
		pthread_mutex_unlock(philo->data->s_mtx);
		return ;
	}
	pthread_mutex_unlock(philo->data->s_mtx);
	philo_stampmod(philo, M_DIE);
}
