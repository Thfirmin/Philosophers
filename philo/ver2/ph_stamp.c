/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_stamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:49 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 20:02:08 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_validlog(t_philo *ph, t_status stat);

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

void	ph_stamplog(t_philo *ph, t_status stat)
{
	time_t		time;
	int			valid;
	const char	*str[] = {
		"has taken a fork",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"is died"
	};

	valid = ph_validlog(ph, stat);
	if (valid)
	{
		pthread_mutex_lock(ph->data->m_philo);
		if (ph_rddt(ph, &ph->data->sim, 0) || 
			ph_rddt(ph, &ph->data->sim, ph->nb))
		{
			time = (ph_getinst(ph->data->start) / 1000);
			printf("%ld %d %s\n", time, ph->nb, str[stat]);
		}
		pthread_mutex_unlock(ph->data->m_philo);
	}
}

static int	ph_validlog(t_philo *ph, t_status stat)
{
	int	live;

	live = ph_islive(ph);
	if (live)
		return (1);
	else if (stat == P_EAT)
		return (1);
	else if ((stat == P_DIE) && (ph_rddt(ph, &ph->data->sim, ph->nb)))
		return (1);
	else
		return (0);
}
