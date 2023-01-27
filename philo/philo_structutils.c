/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 03:41:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/27 16:52:00 by thfirmin         ###   ########.fr       */
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
	law->philo_nbr = philo_atoi(argv[1]);
	law->t_eat = philo_atoi(argv[3]);
	law->t_die = philo_atoi(argv[2]);
	law->t_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		law->eat_nbr = philo_atoi(argv[5]);
	else
		law->eat_nbr = -1;
	law->forks = malloc(law->philo_nbr);
	if (!law->forks)
			return (law);
	while (++i <= law->philo_nbr)
		*(law->forks + i) = '\0';
	printf ("nbr: %d\nt_die: %d\nt_eat: %d\nt_sleep: %d\nnbr_time: %d\n", law->philo_nbr, law->t_die, law->t_eat, law->t_sleep, law->eat_nbr);
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
	while (++i < law->philo_nbr)
	{
		philo[i].nb = i + 1;
		philo[i].eat = 0;
		philo[i].die = 0;
		philo[i].sleep = 0;
		philo[i].eat_nb = law->eat_nbr;
		philo[i].law = law;
		pthread_create(&philo[i].id, NULL, philo_routine, &philo[i]);
		printf ("created philosopher %d\n", i);
	}
	printf ("i: %d < philo_nbr: %d\n", i, law->philo_nbr);
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
	if (law)
	{
		free(law->forks);
		free(law);
	}
	if (philo)
	{
		free(philo);
	}
}
