/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 08:31:43 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/28 03:37:41 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_die(t_philo *philo);

static void	philo_dropfork(t_philo *philo, int life);

static void	philo_takefork(t_philo *philo, int life);

static int	philo_usleep(t_philo *philo, unsigned long int time, int life);

void	*philo_routine(void	*data)
{
	t_philo	*philo;
	int		life;

	philo = data;
	life = 1;
	while(life && philo->law->sim)
	{
			philo_takefork(philo, life);
			philo_messagestamp(philo, M_EAT, life);
			life = philo_usleep(philo, philo->law->t_eat, life);
			philo_dropfork(philo, life);
			philo_messagestamp(philo, M_SLEEP, life);
			life = philo_usleep(philo, philo->law->t_sleep, life);
			philo_messagestamp(philo, M_THINK, life);
			life = philo_usleep(philo, PHILO_THINK, life);
	}
	pthread_mutex_lock(&philo->law->s_mtx);
	if (philo->law->sim)
		philo_die(philo);
	pthread_mutex_unlock(&philo->law->s_mtx);
	return (0);
}

static int	philo_usleep(t_philo *philo, unsigned long int time, int life)
{
	unsigned long int	init;
	unsigned long int	inst;

	if (!life && !philo->law->sim)
		return (0);
	init = (philo_getinstant() / 1000);
	inst = init;
	while ((inst - init) < time)
	{
		inst = (philo_getinstant() / 1000);
		if ((inst - philo->life) >= philo->law->t_die)
			return (0);
	}
	return (1);
}

static void	philo_takefork(t_philo *philo, int life)
{
	int	philo_nbr;
	int	philo_id;

	if (!life && !philo->law->sim)
		return ;
	philo_nbr = philo->law->philo_nbr;
	philo_id = philo->nb;
	if (philo_id % 2)
	{
		pthread_mutex_lock(&philo->law->fork[philo_id % philo_nbr]);
		philo_messagestamp(philo, M_FORK, life);
		pthread_mutex_lock(&philo->law->fork[philo_id - 1]);
		philo_messagestamp(philo, M_FORK, life);
	}
	else
	{
		pthread_mutex_lock(&philo->law->fork[philo_id - 1]);
		philo_messagestamp(philo, M_FORK, life);
		pthread_mutex_lock(&philo->law->fork[philo_id % philo_nbr]);
		philo_messagestamp(philo, M_FORK, life);
	}
	philo->life = (philo_getinstant() / 1000);
}

static void	philo_dropfork(t_philo *philo, int life)
{
	int	philo_nbr;
	int	philo_id;

	if (!life && !philo->law->sim)
		return ;
	philo_nbr = philo->law->philo_nbr;
	philo_id = philo->nb;
	if (philo_id % 2)
	{
		pthread_mutex_unlock(&philo->law->fork[philo_id % philo_nbr]);
		pthread_mutex_unlock(&philo->law->fork[philo_id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->law->fork[philo_id - 1]);
		pthread_mutex_unlock(&philo->law->fork[philo_id % philo_nbr]);
	}
}

static void	philo_die(t_philo *philo)
{
	philo->die = 1;
	philo_messagestamp(philo, M_DIE, 0);
	philo->law->sim = 0;
}
