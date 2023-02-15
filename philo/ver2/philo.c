/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:32 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 13:16:58 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_isvalid_arg(int argc, char *argv[]);

static void	monitoring(t_philo *ph, t_data *dt);

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philo;

	if (!ph_isvalid_arg(argc, argv))
		return (1);
	data = ph_initdata(argc, argv);
	if (!ph_checkdata(data))
		return (2);
	if (data->n_philo && data->t_die && data->n_eat)
	{
		philo = ph_initphilo(data);
		if (!ph_checkphilo(philo, data))
			return (3);
		monitoring(philo, data);
		ph_cleanphilo(&philo, data);
	}
	ph_cleandata(&data);
	return (0);
}

static void	monitoring(t_philo *ph, t_data *dt)
{
	int	idx;

	idx = 0;
	while (1)
	{
		if (idx == dt->n_philo)
			idx = 0;
		if (ph_rdph_stat(&ph[idx], P_DIE))
		{
			ph_wrdt(&ph[idx], &dt->sim, idx + 1, 0);
			ph_die(&ph[idx]);
			break ;
		}
		else if (ph_rdph_stat(&ph[idx], P_EATED))
		{
			ph_wrdt(&ph[idx], &dt->sim, idx + 1, 0);
			break ;
		}
	}
}

static int	ph_isvalid_arg(int argc, char *argv[])
{
	int	i;

	if ((argc < 5) || (argc > 6))
	{
		ph_stamperr(0);
		return (0);
	}
	i = 0;
	while(*(argv + ++i))
	{
		if (!ph_isposnumber(*(argv + i)))
		{
			ph_stamperr("Error: Use just positive decimal number\n");
			return (0);
		}
	}
	return (1);
}
