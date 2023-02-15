/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:19 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 13:58:21 by thfirmin         ###   ########.fr       */
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
		//printf ("%ld philo is live (%d)\n", (ph_getinst(philo->data->start) / 1000), (ph_rdph_stat(philo, P_DIE)));
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
	printf ("EAT COUNT = %ld\n", ph_rdph(ph, &ph->n_eat));
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
/*
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

	// Verify simulation validation
	// Verify philosopher status
	// Iterate eating
	// stamp message
	// usleep wait
}
*/

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
/*
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

	// Verify simulation validation
	// verify philosopher status
	// Stamp message
	// usleep wait
}
*/

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
/*
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
	
	// Verify simulation validation
	// verify philosopher status
	// stamp message
	// usleep wait
}
*/

void	ph_die(t_philo *ph)
{
	// Verify simulation status
	// stamp mod
	ph_stamplog(ph, P_DIE);
}
/*
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
*/
