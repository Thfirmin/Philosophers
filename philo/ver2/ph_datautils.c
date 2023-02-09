/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_datautils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:44 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/09 02:25:43 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*ph_datainit(int argc, char *agrv[])
{
	t_data	*data;

	data = malloc(1 * sizeof(t_data));
	if (!data)
		return (data);
	memset(data, 0, (1 * sizeof(t_data)));
	data->n_philo = ph_atoi(argv[1]);
	data->t_die = (ph_atoi(argv[2]) * 1000);
	data->t_eat = (ph_atoi(argv[3]) * 1000);
	data->t_sleep = (ph_atoi(argv[4]) * 1000);
	data->n_eat = -1;
	data->sim = 1;
	if (argc == 6)
}

int	ph_datacheck()

void	ph_dataclean(t_data *data)
{
	...;
}
