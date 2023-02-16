/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:19 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 20:00:49 by thfirmin         ###   ########.fr       */
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
	// Verify simulation validation
	if (!ph_islive(ph))
		return ;
	// Verify philo status requirements
	if (!ph_rdph_stat(ph, P_FORK2))
		return ;
	// Iterate eat counter
	ph_wrph(ph, &ph->n_eat, 1, 1);
	if (ph_rdph(ph, &ph->n_eat) == ph->data->n_eat)
		ph_wrph_stat(ph, P_EATED, 1);
	// Increment life counter
	pthread_mutex_lock(ph->data->m_philo);
	ph->t_life = ph_getinst(0);
	pthread_mutex_unlock(ph->data->m_philo);
	// Stamp log
	ph_stamplog(ph, P_EAT);
	// write status
	ph_wrph_stat(ph, P_EAT, 1);
	// Usleep t_eat time
	ph_usleep(ph, ph->data->t_eat);
}

void	ph_sleep(t_philo *ph)
{
	// Verify simulation validation
	if (!ph_islive(ph))
		return ;
	// Verify philo status requirements
	if (!ph_rdph_stat(ph, P_EAT))
		return ;
	// stamp log
	ph_stamplog(ph, P_SLEEP);
	// write status
	ph_wrph_stat(ph, P_SLEEP, 0);
	// usleep t_sleep time
	ph_usleep(ph, ph->data->t_sleep);
}

void	ph_think(t_philo *ph)
{
	// Verify simulation validation
	if (!ph_islive(ph))
		return ;
	// varify philo status requirements and stamp log / write status
	if (ph_rdph_stat(ph, P_SLEEP))
	{
		ph_stamplog(ph, P_THINK);
		ph_wrph_stat(ph, P_THINK, 0);
	}
	// usleep if simulation is valid
	ph_usleep(ph, T_THINK);
}

void	ph_die(t_philo *ph)
{
	// Verify simulation status
	// stamp mod
	ph_stamplog(ph, P_DIE);
}
