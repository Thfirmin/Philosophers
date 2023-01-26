/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:27:15 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/26 08:53:46 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_err_message(void);

static int	philo_isvalid_arg(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_law	law;
	t_philo	*philo;

	(void) philo;
	if(!philo_isvalid_arg(argc, argv))
	{
		philo_err_message();
		return (2);
	}
	law = philo_initlaw(argc, argv);
	//philo = philo_initphilo(&law);
	return (0);
}

static int	philo_isvalid_arg(int argc, char *argv[])
{
	if ((argc < 4) || (argc > 5))
		return (0);
	argv++;
	while (*argv)
	{
		if ((**argv == '-') || (**argv == '+'))
			if (*(*argv)++ == '-')
				return (0);
		while (**argv)
		{
			if (!((**argv >= '0') && (**argv <= '9')))
				return (0);
			*argv += 1;
		}
		argv++;
	}
	return (1);
}

static void	philo_err_message(void)
{
	philo_putstr_fd("Usage: ./philo <philos_nbr> <t_die> <t_eat> ", 2);
	philo_putstr_fd("<t_sleep> [nbr_time_philos_to_eat]\n", 2);
}
