/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_rdwr_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:32:27 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 13:57:25 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_wrdt(t_philo *ph, void *data, int aux, short mod)
{
	pthread_mutex_lock(ph->data->m_data);
	if (!mod)
		*(int *)data = aux;
	else if (mod > 0)
		*(int *)data += aux;
	else
		*(int *)data -= aux;
	pthread_mutex_unlock(ph->data->m_data);
}

int	ph_rddt(t_philo *ph, void *data, int cmp)
{
	int	src;

	pthread_mutex_lock(ph->data->m_data);
	src = *(int *)data;
	if (src == cmp)
	{
		pthread_mutex_unlock(ph->data->m_data);
		return (1);
	}
	pthread_mutex_unlock(ph->data->m_data);
	return (0);
}
