/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:19 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 22:07:00 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ph_routine(void *param)
{
	t_philo	*philo;

	philo = param;
	while (ph_islive(philo) || ph_rdph_stat(philo, P_FORK1))
	{
		ph_takeone_fork(philo);
		ph_taketwo_fork(philo);
		ph_eat(philo);
		ph_dropfork(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (0);
}

void	ph_eat(t_philo *ph)
{
	if (!ph_islive(ph))
		return ;
	if (!ph_rdph_stat(ph, P_FORK2))
		return ;
	ph_wrph(ph, &ph->n_eat, 1, 1);
	if (ph_rdph(ph, &ph->n_eat) == ph->data->n_eat)
		ph_wrph_stat(ph, P_EATED, 1);
	pthread_mutex_lock(ph->data->m_philo);
	ph->t_life = ph_getinst(0);
	pthread_mutex_unlock(ph->data->m_philo);
	ph_stamplog(ph, P_EAT);
	ph_wrph_stat(ph, P_EAT, 1);
	ph_usleep(ph, ph->data->t_eat);
}

void	ph_sleep(t_philo *ph)
{
	if (!ph_islive(ph))
		return ;
	if (!ph_rdph_stat(ph, P_EAT))
		return ;
	ph_stamplog(ph, P_SLEEP);
	ph_wrph_stat(ph, P_SLEEP, 0);
	ph_usleep(ph, ph->data->t_sleep);
}

void	ph_think(t_philo *ph)
{
	if (!ph_islive(ph))
		return ;
	if (ph_rdph_stat(ph, P_SLEEP))
	{
		ph_stamplog(ph, P_THINK);
		ph_wrph_stat(ph, P_THINK, 0);
	}
	ph_usleep(ph, T_THINK);
}

void	ph_die(t_philo *ph)
{
	ph_stamplog(ph, P_DIE);
}
