/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_strutils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 02:48:05 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/26 08:54:26 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

int	philo_atoi(char	*ascii)
{
	int	i;
	int	nbr;

	i = philo_strlen(ascii);
	nbr = 0;
	while (--i > -1)
		nbr = ((nbr * 10) + (*(ascii + i) - '0'));
	if (*ascii == '-')
		nbr = -nbr;
	return (nbr);
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
