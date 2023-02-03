/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:15:35 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 18:44:00 by thfirmin         ###   ########.fr       */
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
	if (philo_read((philo->stat & (1 << M_DIE)), philo->m_stat))
		philo_die(philo);
	return (0);
}

void	philo_takeone_fork(t_philo *philo)
{
	int	p_nbr;

	p_nbr = philo->data->n_philo;
	if (!philo_islive(philo))
		return ;
	if (!philo_read((philo->stat & (1 << M_THINK)), philo->m_stat))
		return ;
	if (philo->nb % 2)
		pthread_mutex_lock(&philo->data->fork[philo->nb % p_nbr]);
	else
		pthread_mutex_lock(&philo->data->fork[philo->nb - 1]);
	philo_stampmod(philo, M_FORK1);
}

void	philo_taketwo_fork(t_philo *philo)
{
	int	p_nbr;

	p_nbr = philo->data->n_philo;
	if (!philo_islive(philo))
		return ;
	if (!philo_read((philo->stat & (1 << M_FORK1)), philo->m_stat))
		return ;
	if (philo->data->n_philo < 2)
		return ;
	if (philo->nb % 2)
		pthread_mutex_lock(&philo->data->fork[philo->nb - 1]);
	else
		pthread_mutex_lock(&philo->data->fork[philo->nb % p_nbr]);
	philo_stampmod(philo, M_FORK2);
}

void	philo_drop_fork(t_philo *philo)
{
	int	p_nbr;

	p_nbr = philo->data->n_philo;
	if (philo->nb % 2)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->nb % p_nbr]);
		pthread_mutex_unlock(&philo->data->fork[philo->nb - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->fork[philo->nb - 1]);
		pthread_mutex_unlock(&philo->data->fork[philo->nb % p_nbr]);
	}
}

void	philo_die(t_philo *philo)
{
	if (philo_read(philo->data->unic, philo->data->s_mtx))
		return ;
	philo_write(&philo->data->unic, 1, philo->data->s_mtx);
	philo_stampmod(philo, M_DIE);
}
