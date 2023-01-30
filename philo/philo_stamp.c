/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stamp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:14:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/30 04:31:26 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_stamperr(char *message)
{
	if (!message)
	{
		philo_putstr_fd("Usage: ./philo <philos_nbr> <t_die> <t_eat> ", 2);
		philo_putstr_fd("<t_sleep> [nbr_time_philos_to_eat]\n", 2);
	}
	else
		philo_putstr_fd(message, 2);
}

unsigned long int	philo_getinst(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}

void	philo_stampmod(t_philo *philo, short mod, int life)
{
	short				i;
	unsigned long int	time;
	const char	*str[] = {
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"is died"
	};

	if (philo->stat[M_DIE] && (mod != M_DIE))
		return ;
	if (!life && (mod != M_DIE))
		return ;
	if ((!philo->data->sim) || (mod < 0) || (mod > 4))
		return ;
	i = -1;
	while (++i < 5)
	{
		if (i == mod)
			philo->stat[mod] += 1;
		else
			philo->stat[mod] = 0;
		printf ("mod[%d]: %d\n", i, philo->stat[i]);
	}
	for (int i = 0; i < 5; i ++)
		printf ("mod[%d]: %d\n", i, philo->stat[i]);
	time = ((philo_getinst() - philo->data->instant) / 1000);
	printf("%lu %d %s\n", time, philo->nb, str[mod]);
}
