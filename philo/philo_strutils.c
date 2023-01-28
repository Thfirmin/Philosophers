/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_strutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 02:48:05 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/28 03:38:40 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

int	philo_atoi(char	*str)
{
	int		atoinum;
	short	signal;

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

int	philo_strlen(char *str)
{
	int	len;

	len = 0;
	if (str)
		while ((*str + len))
			len ++;
	return (len);
}

void	philo_messagestamp(t_philo *philo, short mode, int life)
{
	unsigned long int	instant;

	if (!life && (mode != M_DIE))
		return ;
	if (!philo->law->sim)
		return ;
	instant = ((philo_getinstant() - philo->law->instant) / 1000);
	if (mode == M_FORK)
		printf ("%lu %d has taken a fork\n", instant, philo->nb);
	else if (mode == M_UFORK)
		printf ("%lu %d has drop a fork\n", instant, philo->nb);
	else if (mode == M_EAT)
		printf ("%lu %d is eating\n", instant, philo->nb);
	else if (mode == M_SLEEP)
		printf ("%lu %d is sleeping\n", instant, philo->nb);
	else if (mode == M_THINK)
		printf ("%lu %d is thinking\n", instant, philo->nb);
	else if (mode == M_DIE)
		printf ("%lu %d is died\n", instant, philo->nb);
}
