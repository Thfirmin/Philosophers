/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 04:54:19 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/20 05:25:39 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(void)
{
	int	ret;
	struct timeval tv;
	struct timezone tz;

	ret = gettimeofday(&tv, &tz);
	printf ("Return: %d\n", ret);
	printf ("timeval:\ntv_sec = %li\ntv_usec = %i\n", (tv.tv_sec * 1000), tv.tv_usec);
	printf ("timezone:\ntz_minuteswest = %d\ntz_dsttime = %d\n", tz.tz_minuteswest, tz.tz_dsttime);
	printf ("MILISECONDS: %li\n", ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
	return (0);
}
