/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 02:15:35 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/30 04:26:32 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_die(t_philo *philo);

void	philo_drop_fork(t_philo *philo, int *life);

void	philo_taketwo_fork(t_philo *philo, int *life);

void	philo_takeone_fork(t_philo *philo, int *life);

void	*philo_routine(void *param)
{
	t_philo	*philo;
	int		life;

	philo = param;
	life = 1;
	while (life && !philo->stat[M_DIE] && philo->data->sim)
	{
		philo_takeone_fork(philo, &life);
		philo_taketwo_fork(philo, &life);
		philo_eat(philo, &life);
		philo_drop_fork(philo, &life);
		philo_sleep(philo, &life);
		philo_think(philo, &life);
		if (philo->data->n_philo < 2)
			life = philo_usleep(philo, philo->data->t_die, life);
	}
	if (!life || philo->stat[M_DIE])
		philo_die(philo);
	return (0);
}

void	philo_takeone_fork(t_philo *philo, int *life)
{
	int					p_nbr;
	unsigned long int	time;

	if (philo->stat[M_DIE])
		return ;
	if (!*life || !philo->data->sim)
		return ;
	if (!philo->stat[M_THINK])
		return ;
	p_nbr = philo->data->n_philo;
	if (philo->nb % 2)
	{
		pthread_mutex_lock(&philo->data->fork[philo->nb % p_nbr]);
		philo_stampmod(philo, M_FORK, *life);
		printf ("forks: %d\n", philo->stat[M_FORK]);
	}
	else
	{
		pthread_mutex_lock(&philo->data->fork[philo->nb - 1]);
		philo_stampmod(philo, M_FORK, *life);
	}
	time = (philo_getinst() / 1000);
	if ((time - philo->t_life) >= philo->data->t_die)
		*life = 0;
}

void	philo_taketwo_fork(t_philo *philo, int *life)
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

void	philo_die(t_philo *philo)
{
	philo_stampmod(philo, M_DIE, 0);
	pthread_mutex_lock(philo->data->s_mtx);
	if (philo->data->sim)
		philo->data->sim = 0;
	pthread_mutex_unlock(philo->data->s_mtx);
}
