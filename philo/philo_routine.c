/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 08:31:43 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/27 16:18:00 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void	*data)
{
	t_philo	*philo;

	philo = data;
	printf ("Log in from philosopher %d\n", philo->nb);
	printf ("Log out from philosopher %d\n", philo->nb);
	return (0);
}
