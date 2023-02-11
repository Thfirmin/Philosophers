/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:33:40 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/10 17:05:44 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_isposnumber(char *nbr)
{
	while (((*nbr >= 9) && (*nbr <= 13)) || (*nbr == ' '))
		nbr ++;
	if ((*nbr == '-') || (*nbr == '+'))
		if (*nbr++ == '-')
			return (0);
	if (!*nbr)
		return (0);
	while (*nbr)
	{
		if ((*nbr < '0') || (*nbr > '9'))
			return (0);
		nbr++;
	}
	return (1);
}

void	ph_putstr_fd(char *str, int fd)
{
	if (str)
		while (*str)
			write (fd, str++, 1);
}

time_t	ph_atol(char *str)
{
	time_t	nbr;
	short	sign;

	nbr = 0;
	if (!str)
		return (0);
	while (((*str >= 9) && (*str <= 13)) || (*str == ' '))
		str ++;
	sign = 1;
	if ((*str == '+') || (*str == '-'))
		if (*str++ == '-')
			sign = -1;
	while ((*str >= '0') && (*str <= '9'))
		nbr = ((nbr * 10) + (*str++ - '0'));
	return (nbr * sign);
}
