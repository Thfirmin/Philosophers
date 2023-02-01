/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:15:35 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/31 22:19:11 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *param)
{
	t_philo	*philo;

	philo = param;
	printf ("Login philo %d with stat %d (%d)\n", philo->nb, philo->stat, (philo->stat & (1 << M_THINK)));
	philo_takeone_fork(philo);
	printf ("philo %d with stat %d (%d)\n", philo->nb, philo->stat, (philo->stat & (1 << M_FORK1)));
	philo_taketwo_fork(philo);
	printf ("philo %d with stat %d (%d)\n", philo->nb, philo->stat, (philo->stat & (1 << M_FORK2)));
	philo_eat(philo);
	printf ("philo %d with stat %d (%d)\n", philo->nb, philo->stat, (philo->stat & (1 << M_EAT)));
	philo_sleep(philo);
	printf ("philo %d with stat %d (%d)\n", philo->nb, philo->stat, (philo->stat & (1 << M_SLEEP)));
	philo_sleep(philo);
	philo_think(philo);
	printf ("Logout philo %d with stat %d (%d)\n", philo->nb, philo->stat, (philo->stat & (1 << M_THINK)));
	return (0);
}

void	philo_takeone_fork(t_philo *philo)
{
	if (!(philo->stat & (1 << M_THINK)))
		return ;
	if (!philo->data->sim)
		return ;
	philo_stampmod(philo, M_FORK1);
}

void	philo_taketwo_fork(t_philo *philo)
{
	if (!philo->data->sim)
		return ;
	if (!(philo->stat & (1 << M_FORK1)) || (philo->data->n_philo < 2))
		return ;
	philo_stampmod(philo, M_FORK2);
}
/*
void	philo_takeone_fork(t_philo *philo)
{
	int					p_nbr;
	unsigned long int	time;

	if (!philo->data->sim)
		return ;
	if (!(philo->stat & (1 << M_THINK)) || !(philo->stat & (1 << M_DIE)))
		return ;
	p_nbr = philo->data->n_philo;
	if (philo->nb % 2)
	{
		pthread_mutex_lock(&philo->data->fork[philo->nb % p_nbr]);
		philo_stampmod(philo, M_FORK1);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->nb - 1]);
		philo_stampmod(philo, M_FORK1);
	}
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		philo->stat = 1 << M_DIE;
}
*/
/*void	philo_taketwo_fork(t_philo *philo, int *life)
{
	int					p_nbr;
	unsigned long int	time;

	if (philo->stat[M_DIE])
		return ;
	if (!*life || !philo->data->sim)
		return ;
	if (!philo->stat[M_FORK])
		return ;
	p_nbr = philo->data->n_philo;
	if (philo->nb % 2)
	{
		pthread_mutex_lock(&philo->data->fork[philo->nb - 1]);
		philo_stampmod(philo, M_FORK, *life);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->nb % p_nbr]);
		philo_stampmod(philo, M_FORK, *life);
	}
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		*life = 0;
}
*/
/*
void	philo_drop_fork(t_philo *philo, int *life)
{
	int					p_nbr;
	unsigned long int	time;

	if (philo->stat[M_DIE])
		return ;
	if (!*life || !philo->data->sim)
		return ;
	if (!philo->stat[M_EAT])
		return ;
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
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		*life = 0;
}
*/
/*
void	philo_die(t_philo *philo)
{
	philo_stampmod(philo, M_DIE, 0);
	pthread_mutex_lock(philo->data->s_mtx);
	if (philo->data->sim)
		philo->data->sim = 0;
	pthread_mutex_unlock(philo->data->s_mtx);
}
*/
