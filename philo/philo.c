/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:27:15 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/28 03:29:35 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_err_message(void);

static int	philo_isvalid_arg(int argc, char *argv[]);

static void	run_monitor(t_philo *philo, t_law *law);

int	main(int argc, char *argv[])
{
	t_law	*law;
	t_philo	*philo;

	if(!philo_isvalid_arg(argc, argv))
	{
		philo_err_message();
		return (2);
	}
	law = philo_initlaw(argc, argv);
	if (!law || !law->fork)
	{
		philo_clean_data(law, 0);
		return (2);
	}
	philo = philo_initphilo(law);
	if (!philo)
	{
		philo_clean_data(law, 0);
		return (2);
	}
	run_monitor(philo, law);
	philo_join(philo, law);
	return (0);
}

static void	run_monitor(t_philo *philo, t_law *law)
{
	int	i;

	while (law->sim)
	{
		i = -1;
		while (++i < law->philo_nbr)
		{
			if (philo[i].die)
			{
				law->sim = 0;
				break;
			}
		}
	}
}

static int	philo_isvalid_arg(int argc, char *argv[])
{
	int	i;
	char	*av;

	if ((argc < 4) || (argc > 5))
		return (0);
	i = 1;
	av = *(argv + i);
	while (av)
	{
		if ((*av == '-') || (*av == '+'))
			if (*av++ == '-')
				return (0);
		while (*av)
		{
			if (!((*av >= '0') && (*av <= '9')))
				return (0);
			av += 1;
		}
		av = *(argv + ++i);
	}
	return (1);
}

static void	philo_err_message(void)
{
	philo_putstr_fd("Usage: ./philo <philos_nbr> <t_die> <t_eat> ", 2);
	philo_putstr_fd("<t_sleep> [nbr_time_philos_to_eat]\n", 2);
}
