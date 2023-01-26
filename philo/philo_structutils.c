/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structutils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 03:41:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/26 08:45:17 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_law	philo_initlaw(int argc, char *argv[])
{
	t_law	law;
	int		i = -1;

	law.philo_nbr = philo_atoi(argv[1]);
	law.t_eat = philo_atoi(argv[3]);
	law.t_die = philo_atoi(argv[2]);
	law.t_sleep = philo_atoi(argv[4]);
	if (argc == 6)
		law.eat_nbr = philo_atoi(argv[5]);
	else
		law.eat_nbr = -1;
	law.forks = malloc(law.philo_nbr);
	while (++i <= law.philo_nbr)
		*(law.forks + i) = '\0';
	return (law);
}

t_philo	*philo_initphilo(t_law *law)
{
	(void)law;
	return (0);
}

