/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_stamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:49 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/11 09:34:11 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	ph_getinst(time_t start)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000000 + tv.tv_usec) - start);
}

void	ph_stamperr(char *message)
{
	if (!message)
	{
		ph_putstr_fd("Usage: ./philo <nbr_of_philos_nbr> <time_to_die> ", 2);
		ph_putstr_fd("<time_to_eat> <time_to_sleep> ", 2);
		ph_putstr_fd("[nbr_time_philos_to_eat]\n", 2);
	}
	else
		ph_putstr_fd(message, 2);
}

void	ph_stampmod(t_philo *ph, int mod)
{
	time_t	time;
	const char	*str[] = {
		"has taken a fork",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"is died"
	};

	if (!ph_islive(ph) && (mod != P_DIE))
		return ;
	pthread_mutex_lock(ph->data->m_philo);
	if (mod != P_FORK1)
		ph->stat |= (1 << mod);
	else
		ph->stat = (1 << mod);
	pthread_mutex_unlock(ph->data->m_philo);
	time = (ph_getinst(ph->data->start) / 1000);
	printf("%ld %d %s\n", time, ph->nb, str[mod]);
}

void	ph_rmstat(t_philo *ph, int mod)
{
	pthread_mutex_lock(ph->data->m_philo);
	ph->stat |= (1 << mod);
	ph->stat ^= (1 << mod);
	pthread_mutex_unlock(ph->data->m_philo);
}
