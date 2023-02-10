/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_datautils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:44 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/09 23:57:03 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ph_initdata(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (data);
	memset(data, 0, (1 * sizeof(t_data)));
	data->n_philo = ph_atol(argv[1]);
	data->t_die = (ph_atol(argv[2]) * 1000);
	data->t_eat = (ph_atol(argv[3]) * 1000);
	data->t_sleep = (ph_atol(argv[4]) * 1000);
	data->n_eat = -1;
	data->sim = 1;
	if (argc == 6)
		data->n_eat = ph_atol(argv[5]);
	else
		data->n_eat = -1;
	data->m_data = ph_initmutex();
	data->m_philo = ph_initmutex();
	return (data);
}

void	ph_cleandata(t_data **data)
{
	t_data *tmp;

	tmp = *data;
	if (!tmp)
		return ;
	ph_destroymutex(&tmp->m_data);
	ph_destroymutex(&tmp->m_philo);
	free(*data);
	*data = 0;
}
