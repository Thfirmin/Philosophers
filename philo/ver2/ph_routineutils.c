/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_routineutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:32 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/11 09:35:17 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_islive(t_philo *ph)
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
}

void	ph_takeone_fork(t_philo *ph)
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
}

void	ph_taketwo_fork(t_philo *ph)
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
}

void	ph_dropfork(t_philo *ph)
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
}

void	ph_usleep(t_philo *ph, time_t t_mcs)
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
}
