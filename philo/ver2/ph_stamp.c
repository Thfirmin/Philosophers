/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_stamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:16:49 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 13:33:56 by thfirmin         ###   ########.fr       */
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

void	ph_stamplog(t_philo *ph, t_status stat)
{
	time_t		time;
	int			ret;
	const char	*str[] = {
		"has taken a fork",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking",
		"is died"
	};

	ret = ph_islive(ph);
	if (ret || (!ret && ((stat == P_DIE) || (stat == P_EATED))))
	{
		time = (ph_getinst(ph->data->start) / 1000);
		printf("%ld %d %s\n", time, ph->nb, str[stat]);
	}
}
