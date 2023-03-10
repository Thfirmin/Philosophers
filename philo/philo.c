/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:32 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/16 13:59:46 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_isvalid_arg(int argc, char *argv[]);

static int	ph_eat_count(t_philo *ph, t_data *dt);

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
	int		idx;
	int		eats;
	time_t	instant;

	idx = -1;
	eats = 1;
	while (eats)
	{
		if (++idx == dt->n_philo)
			idx = 0;
		instant = ph_getinst(0);
		if ((instant - ph_rdph_tlife(&ph[idx])) >= dt->t_die)
			ph_wrph_stat(&ph[idx], P_DIE, 1);
		if (ph_rdph_stat(&ph[idx], P_DIE))
		{
			ph_wrdt(&ph[idx], &dt->sim, ph[idx].nb, 0);
			ph_die(&ph[idx]);
			break ;
		}
		eats = ph_eat_count(ph, dt);
		usleep(1000);
	}
}

static int	ph_eat_count(t_philo *ph, t_data *dt)
{
	int	i;
	int	eats;

	eats = 0;
	i = -1;
	while (++i < dt->n_philo)
		if (ph_rdph_stat(&ph[i], P_EATED))
			eats ++;
	if (eats == dt->n_philo)
		return (0);
	return (1);
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
	while (*(argv + ++i))
	{
		if (!ph_isposnumber(*(argv + i)))
		{
			ph_stamperr("Error: Use just positive decimal number\n");
			return (0);
		}
	}
	return (1);
}
