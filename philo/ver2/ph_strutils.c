/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:33:40 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/09 01:45:20 by thfirmin         ###   ########.fr       */
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
