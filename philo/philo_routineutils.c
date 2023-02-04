/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routineutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:16:50 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 23:52:39 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	if (!philo_islive(philo))
		return ;
	if (!philo_read((philo->stat & (1 << M_FORK2)), philo->m_stat))
		return ;
	philo->t_life = philo_getinst();
	philo_stampmod(philo, M_EAT);
	philo_write(&philo->n_eat, (philo->n_eat + 1), philo->m_stat);
	philo_usleep(philo, philo->data->t_eat);
}

void	philo_sleep(t_philo *philo)
{
	if (!philo_islive(philo))
		return ;
	if (!philo_read((philo->stat & (1 << M_EAT)), philo->m_stat))
		return ;
	philo_stampmod(philo, M_SLEEP);
	philo_usleep(philo, philo->data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	if (!philo_islive(philo))
		return ;
	if (philo_read((philo->stat & (1 << M_SLEEP)), philo->m_stat))
		philo_stampmod(philo, M_THINK);
	philo_usleep(philo, PHILO_THINK);
}

int	philo_islive(t_philo *philo)
{
	if (philo_read((philo->stat & (1 << M_DIE)), philo->m_stat))
		return (0);
	else if (!philo_read(philo->data->sim, philo->data->s_mtx))
		return (0);
	else if (philo_read((philo->n_eat == philo->data->n_eat), philo->m_stat))
		return (0);
	return (1);
}

void	philo_usleep(t_philo *philo, unsigned long int time)
{
	unsigned long int	init;
	unsigned long int	inst;

	if (!philo_islive(philo))
		return ;
	init = philo_getinst();
	inst = init;
	while (((inst - init) < time) && (philo_islive(philo)))
	{
		inst = philo_getinst();
		if ((inst - philo->t_life) >= philo->data->t_die)
		{
			philo_write(&philo->stat, (philo->stat | (1 << M_DIE)),
				philo->m_stat);
			philo_write(&philo->data->sim, 0, philo->data->s_mtx);
			return ;
		}
		usleep(250);
	}
}
