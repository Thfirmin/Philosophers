/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:15:32 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/09 23:09:43 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ph_isvalid_arg(int argc, char *argv[]);

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (!ph_isvalid_arg(argc, argv))
		return (2);
	//printf ("Initializing data...\n");
	data = ph_initdata(argc, argv);
	//printf ("Data initialized\nErasing data...\n");
	ph_cleandata(&data);
	//printf ("Data erased\n");
	return (0);
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
	while(*(argv + ++i))
	{
		if (!ph_isposnumber(*(argv + i)))
		{
			ph_stamperr("Error: Use just positive decimal number\n");
			return (0);
		}
	}
	return (1);
}
