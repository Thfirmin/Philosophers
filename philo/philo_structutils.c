/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 03:41:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/28 03:58:47 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_law	*philo_initlaw(int argc, char *argv[])
{
	t_law	*law;
	int		i = -1;

	law = malloc (sizeof(t_law));
	if (!law)
		return (0);
	law->sim = 1;
	pthread_mutex_init(&law->s_mtx, 0);
	law->philo_nbr = philo_atoi(argv[1]);
	law->t_eat = philo_atoi(argv[3]);
	law->t_die = philo_atoi(argv[2]);
	law->t_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		law->eat_nbr = philo_atoi(argv[5]);
	else
		law->eat_nbr = -1;
	law->fork = malloc(sizeof(pthread_mutex_t) * law->philo_nbr);
	if (!law->fork)
			return (law);
	while (++i < law->philo_nbr)
		pthread_mutex_init((law->fork + i), 0);
	return (law);
}

t_philo	*philo_initphilo(t_law *law)
{
	t_philo *philo;
	int		i;

	philo = malloc(law->philo_nbr * sizeof(t_philo));
	if (!philo)
		return (0);
	i = -1;
	law->instant = philo_getinstant();
	while (++i < law->philo_nbr)
	{
		philo[i].nb = i + 1;
		philo[i].life = (philo_getinstant() / 1000);
		philo[i].die = 0;
		philo[i].eat_nb = law->eat_nbr;
		philo[i].law = law;
		pthread_create(&philo[i].id, NULL, philo_routine, &philo[i]);
	}
	return (philo);
}

void	philo_join(t_philo *philo, t_law *law)
{
	int	i;

	i = -1;
	while (++i < law->philo_nbr)
		pthread_join(philo[i].id, NULL);
	philo_clean_data(law, philo);
}

void	philo_clean_data(t_law *law, t_philo *philo)
{
	int	i;

	i = -1;
	if (law)
	{
		pthread_mutex_destroy(&law->s_mtx);
		if (law->fork)
			while (++i < law->philo_nbr)
				pthread_mutex_destroy(&law->fork[i]);
		free(law->fork);
		free(law);
	}
	if (philo)
	{
		free(philo);
	}
}
