/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_getinstant.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:20:55 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/22 17:57:41 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// gettimeofday in milisenconds
long int	philo_getinstant(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return ((tv.tv_sec * 1000000) + tv.tv_usec);
}
