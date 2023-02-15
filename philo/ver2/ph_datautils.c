/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_datautils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:44 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 13:48:31 by thfirmin         ###   ########.fr       */
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
	data->sim = 0;
	data->n_eat = -1;
	if (argc == 6)
		data->n_eat = ph_atol(argv[5]);
	data->m_data = ph_initmutex();
	data->m_philo = ph_initmutex();
	data->fork = ph_initfork(data);
	return (data);
}

int	ph_checkdata(t_data *data)
{
	int	i;
	int	ret;

	ret = 1;
	if (!data)
	{
		ph_stamperr("Error: Data allocation failed\n");
		return (0);
	}
	if (!data->m_data || !data->m_philo || !data->fork)
		ret = 0;
	i = -1;
	while (ret && (++i < data->n_philo))
		if (!*(data->fork + i))
			ret = 0;
	if (!ret)
	{
		ph_stamperr("Error: Mutex initialization failed\n");
		ph_cleandata(&data);
	}
	return (ret);
}

void	ph_cleandata(t_data **data)
{
	t_data *tmp;

	tmp = *data;
	if (!tmp)
		return ;
	ph_destroymutex(&tmp->m_data);
	ph_destroymutex(&tmp->m_philo);
	ph_destroyfork(tmp, &tmp->fork);
	free(*data);
	*data = 0;
}
