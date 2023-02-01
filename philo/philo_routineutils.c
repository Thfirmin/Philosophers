/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routineutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:16:50 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/01 02:55:56 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	unsigned long int	time;

	if (!philo->data->sim || (philo->stat & (1 << M_DIE)))
		return ;
	if (!(philo->stat & (1 << M_FORK2)))
		return ;
	philo_stampmod(philo, M_EAT);
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		philo->stat = 1 << M_DIE;
}

void	philo_sleep(t_philo *philo)
{
	unsigned long int	time;

	if (!philo->data->sim || (philo->stat & (1 << M_DIE)))
		return ;
	if (!(philo->stat & (1 << M_EAT)))
		return ;
	philo_stampmod(philo, M_SLEEP);
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		philo->stat = 1 << M_DIE;
}

void	philo_think(t_philo *philo)
{
	unsigned long int	time;

	if (!philo->data->sim || (philo->stat & (1 << M_DIE)))
		return ;
	if ((philo->stat & (1 << M_SLEEP)))
		philo_stampmod(philo, M_THINK);
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		philo->stat = 1 << M_DIE;
}

/*int	philo_usleep(t_philo *philo, unsigned long int time, int life)
{
	unsigned long int	init;
	unsigned long int	inst;

	if (philo->stat[M_DIE])
		return (0);
	if (!life || !philo->data->sim)
		return (0);
	init = (philo_getinst() / 1000);
	inst = init;
	while ((inst - init) < time)
	{
		inst = (philo_getinst() / 1000);
		if ((inst - philo->t_life) >= philo->data->t_die)
			return (0);
	}
	return (1);
}
*/
/*
void	philo_eat(t_philo *philo, int *life)
{
	unsigned long int	time;

	if (philo->stat[M_DIE])
		return ;
	if (!*life || !philo->data->sim)
		return ;
	if (philo->stat[M_FORK] != 2)
		return ;
	philo->t_life = philo_getinst();
	*life = philo_usleep(philo, philo->data->t_eat, *life);
	philo_stampmod(philo, M_EAT, *life);
	philo->stat[N_EAT] ++;
	if (philo->stat[N_EAT] == philo->data->n_eat)
	{
		pthread_mutex_lock(philo->data->s_mtx);
		philo->data->sim = 0;
		pthread_mutex_unlock(philo->data->s_mtx);
		return ;
	}
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		*life = 0;
}
*/
/*
void	philo_sleep(t_philo *philo, int *life)
{
	unsigned long int	time;

	if (philo->stat[M_DIE])
		return ;
	if (!*life || !philo->data->sim)
		return ;
	if (!philo->stat[M_EAT])
		return ;
	*life = philo_usleep(philo, philo->data->t_sleep, *life);
	philo_stampmod(philo, M_SLEEP, *life);
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		*life = 0;
}
*/
/*
void	philo_think(t_philo *philo, int *life)
{
	unsigned long int	time;

	if (philo->stat[M_DIE])
		return ;
	if (!*life || !philo->data->sim)
		return ;
	if(philo->stat[M_SLEEP])
		philo_stampmod(philo, M_THINK, *life);
	*life = philo_usleep(philo, PHILO_THINK, *life);
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		*life = 0;
}
*/
