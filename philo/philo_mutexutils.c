/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mutexutils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:39:41 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 23:49:55 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_read(int dst, pthread_mutex_t *mtx)
{
	pthread_mutex_lock(mtx);
	if (dst)
	{
		pthread_mutex_unlock(mtx);
		return (1);
	}
	pthread_mutex_unlock(mtx);
	return (0);
}

void	philo_write(void *dst, int src, pthread_mutex_t *mtx)
{
	int	*ptr;

	pthread_mutex_lock(mtx);
	ptr = (int *) dst;
	*ptr = src;
	pthread_mutex_unlock(mtx);
}
