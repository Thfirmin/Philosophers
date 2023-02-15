/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routineutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:32 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 20:01:17 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_islive(t_philo *ph)
{
	// Verify simulation validation and;
	// Verify philo's dead status and;
	// Verify philo's eat number.
	if (!ph_rddt(ph, &ph->data->sim, 0))
		return (0);
	else if (ph_rdph_stat(ph, P_DIE))
		return (0);
	else if (ph_rdph_stat(ph, P_EATED))
		return (0);
	return (1);
}

void	ph_takeone_fork(t_philo *ph)
{
	// Verify simulation validation
	if (!ph_islive(ph))
		return ;
	// Verify step requirements
	if (!ph_rdph_stat(ph, P_THINK))
		return ;
	// Take fork
	if (ph->nb % 2)
		pthread_mutex_lock(ph->data->fork[ph->nb % ph->data->n_philo]);
	else
		pthread_mutex_lock(ph->data->fork[ph->nb - 1]);
	// Stamp log
	ph_stamplog(ph, P_FORK1);
	// Write philo status
	ph_wrph_stat(ph, P_FORK1, 0);
}	

void	ph_taketwo_fork(t_philo *ph)
{
	// Verify simulation validation
	if (!ph_islive(ph))
		return ;
	// Verify step requirements
	if ((!ph_rdph_stat(ph, P_FORK1)) || (ph->data->n_philo < 2))
		return ;
	// Take two fork
	if (ph->nb % 2)
		pthread_mutex_lock(ph->data->fork[ph->nb - 1]);
	else
		pthread_mutex_lock(ph->data->fork[ph->nb % ph->data->n_philo]);
	// Stamp log
	ph_stamplog(ph, P_FORK2);
	// Write philo status
	ph_wrph_stat(ph, P_FORK2, 1);
}

void	ph_dropfork(t_philo *ph)
{
	// Verify philo status for first fork
	if (ph_rdph_stat(ph, P_FORK1))
	{
		// drop philo first fork
		if (ph->nb % 2)
			pthread_mutex_unlock(ph->data->fork[ph->nb % ph->data->n_philo]);
		else
			pthread_mutex_unlock(ph->data->fork[ph->nb - 1]);
		// Remove first fork status
		ph_wrph_stat(ph, P_FORK1, -1);
	}
	// verify philo status for second fork
	if (ph_rdph_stat(ph, P_FORK2))
	{
		// Drop philo second fork
		if (ph->nb % 2)
			pthread_mutex_unlock(ph->data->fork[ph->nb - 1]);
		else
			pthread_mutex_unlock(ph->data->fork[ph->nb % ph->data->n_philo]);
		// Remove second fork status
		ph_wrph_stat(ph, P_FORK2, -1);
	}
}

void	ph_usleep(t_philo *ph, time_t t_mcs)
{
	// Take start time
	time_t	start;
	time_t	inst;

	start = ph_getinst(0);
	inst = start;
	// Wait until difference of start end actual time correspond of gap time
	while (ph_islive(ph) && ((inst - start) <  t_mcs))
	{
		inst = ph_getinst(0);
		// Interromp if philo's dead
		if ((inst - ph_rdph_tlife(ph)) >= ph->data->t_die)
		{
			if (ph_rddt(ph, &ph->data->sim, 0))
				ph_wrdt(ph, &ph->data->sim, ph->nb, 0);
			ph_wrph_stat(ph, P_DIE, 1);
			break ;
		}
		usleep (100);
	}
}
