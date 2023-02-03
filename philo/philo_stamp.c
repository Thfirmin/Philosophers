/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stamp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:14:02 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 11:26:02 by thfirmin         ###   ########.fr       */
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


void	philo_stampmod(t_philo *philo, short mod)
{
	unsigned long int	time;
	const char	*str[] = {
		"has taken a fork",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"is died"
	};

	if (!philo_islive(philo) && !(mod == M_DIE))
		return ;
	pthread_mutex_lock(philo->m_stat);
	philo->stat = (1 << mod);
	pthread_mutex_unlock(philo->m_stat);
	time = ((philo_getinst() - philo->data->instant) / 1000);
	printf("%lu %d %s\n", time, philo->nb, str[mod]);
}

