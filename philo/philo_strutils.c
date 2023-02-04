/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_strutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 21:00:54 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 23:51:30 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_isposnumber(char *str)
{
	if ((*str == '-') || (*str == '+'))
		if (*str++ == '-')
			return (0);
	while (*str)
	{
		if ((*str < '0') || (*str > '9'))
			return (0);
		str ++;
	}
	return (1);
}

void	philo_putstr_fd(char *str, int fd)
{
	while (*str)
		write (fd, str++, 1);
}

unsigned long int	philo_atol(char *str)
{
	unsigned long int	atoinum;
	short				signal;

	signal = 1;
	atoinum = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal = (signal * -1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		atoinum = (atoinum * 10);
		atoinum = (atoinum + (*str - '0'));
		str++;
	}
	atoinum = (atoinum * signal);
	return (atoinum);
}
