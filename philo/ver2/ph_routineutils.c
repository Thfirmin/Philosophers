/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routineutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:32 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 13:44:26 by thfirmin         ###   ########.fr       */
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
/*
{
	int	eat;

	pthread_mutex_lock(ph->data->m_data);
	if (!ph->data->sim)
	{
		pthread_mutex_unlock(ph->data->m_data);
		return (0);
	}
	eat = ph->data->n_eat;
	pthread_mutex_unlock(ph->data->m_data);
	pthread_mutex_lock(ph->data->m_philo);
	if ((ph->stat & (1 << P_DIE)) || (ph->n_eat == eat))
	{
		pthread_mutex_unlock(ph->data->m_philo);
		return (0);
	}
	pthread_mutex_unlock(ph->data->m_philo);
	return (1);
	
	// Verify simulation
	// Verify dead status
	// Verify eating count
}
*/
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
/*
{
	unsigned char	stat;
	int				p_nbr;

	if (!ph_islive(ph))
		return ;
	pthread_mutex_lock(ph->data->m_philo);
	stat = ph->stat;
	pthread_mutex_unlock(ph->data->m_philo);
	p_nbr = ph->data->n_philo;
	if (!(stat & (1 << P_THINK)))
		return ;
	if (ph->nb % 2)
		pthread_mutex_lock(ph->data->fork[ph->nb % p_nbr]);
	else
		pthread_mutex_lock(ph->data->fork[ph->nb - 1]);
	ph_stampmod(ph, P_FORK1);

	// Verify simulation validation
	// Verify philospher status
	// Take mutex fork
	// Stamp message
}
*/
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
/*
{
	unsigned char	stat;
	int				p_nbr;

	if (!ph_islive(ph))
		return ;
	pthread_mutex_lock(ph->data->m_philo);
	stat = ph->stat;
	pthread_mutex_unlock(ph->data->m_philo);
	p_nbr = ph->data->n_philo;
	if (!(stat & (1 << P_FORK1)) || (p_nbr < 2))
		return ;
	if (ph->nb % 2)
		pthread_mutex_lock(ph->data->fork[ph->nb - 1]);
	else
		pthread_mutex_lock(ph->data->fork[ph->nb % p_nbr]);
	ph_stampmod(ph, P_FORK2);

	// Verify simulation validation
	// Verify philosopher status
	// Take mutex fork
	// Stamp message
}
*/
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
/*
{
	unsigned char	stat;
	int				p_nbr;

	pthread_mutex_lock(ph->data->m_philo);
	stat = ph->stat;
	pthread_mutex_unlock(ph->data->m_philo);
	p_nbr = ph->data->n_philo;
	if (ph->nb % 2)
	{
		if (stat & (1 << P_FORK2))
			pthread_mutex_unlock(ph->data->fork[ph->nb % p_nbr]);
		if (stat & (1 << P_FORK1))
			pthread_mutex_unlock(ph->data->fork[ph->nb - 1]);
	}
	else
	{
		if (stat & (1 << P_FORK1))
			pthread_mutex_unlock(ph->data->fork[ph->nb - 1]);
		if (stat & (1 << P_FORK2))
			pthread_mutex_unlock(ph->data->fork[ph->nb % p_nbr]);
	}
	ph_rmstat(ph, P_FORK1);
	ph_rmstat(ph, P_FORK2);
	
	// Verify philosopher status
	// Drop philosopher fork
	// Delete fork status
}
*/
void	ph_usleep(t_philo *ph, time_t t_mcs)
{
	// Take start time
	time_t	start;
	time_t	inst;

	start = ph_getinst(0);
	inst = start;
	// Wait until difference of start end actual time correspond of gap time
	while ((inst - start) <  t_mcs)
	{
		inst = ph_getinst(0);
		// Interromp if philo's dead
		if ((inst - ph_rdph(ph, &ph->t_life)) >= ph->data->t_die)
		{
			ph_wrph_stat(ph, P_DIE, 1);
			break ;
		}
		usleep (100);
	}
}
/*
{
	time_t	begin;
	time_t	inst;
	time_t	t_life;

	begin = ph_getinst(0);
	inst = begin;
	pthread_mutex_lock(ph->data->m_philo);
	t_life = ph->t_life;
	pthread_mutex_unlock(ph->data->m_philo);
	while (ph_islive(ph) && ((inst - begin) < t_mcs))
	{
		inst = ph_getinst(0);
		pthread_mutex_lock(ph->data->m_data);
		if ((inst - t_life) >= ph->data->t_die)
		{
			ph->data->sim = 0;
			pthread_mutex_unlock(ph->data->m_data);
			pthread_mutex_lock(ph->data->m_philo);
			ph->stat |= (1 << P_DIE);
			pthread_mutex_unlock(ph->data->m_philo);
			return ;
		}
		pthread_mutex_unlock(ph->data->m_data);
		usleep(150);
	}

	// wait untils simulation's over or philo's die
}
*/
