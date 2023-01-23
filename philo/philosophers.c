/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:27:15 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/22 21:18:19 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Passo 1:
// Passo 2:
// Passo 3:
// Passo 4:


int				puta = 0;
pthread_mutex_t	cadeado;

void	*mete_a_mao(void *status)
{
	(void) status;
	for (int i = 1; i <= 5000; i ++)
	{
		//pthread_mutex_lock(&cadeado);
		puta ++;
		//pthread_mutex_unlock(&cadeado);
	}
	return (0);
}

int	main(void)
{
	pthread_t	thread1;
	pthread_t	thread2;
	pthread_t	thread3;
	pthread_t	thread4;
	pthread_t	thread5;
	pthread_t	thread6;
	pthread_t	thread7;
	pthread_t	thread8;
	pthread_t	thread9;
	pthread_t	thread0;
	void		*fds;

	printf ("%ld\n", philo_getinstant());	
	pthread_mutex_init(&cadeado, (void *)0);
	pthread_create(&thread1, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread2, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread3, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread4, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread5, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread6, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread7, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread8, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread9, (void *)0, mete_a_mao, (void *)0);
	pthread_create(&thread0, (void *)0, mete_a_mao, (void *)0);
	pthread_join(thread1, &fds);
	pthread_join(thread2, &fds);
	pthread_join(thread3, &fds);
	pthread_join(thread4, &fds);
	pthread_join(thread5, &fds);
	pthread_join(thread6, &fds);
	pthread_join(thread7, &fds);
	pthread_join(thread8, &fds);
	pthread_join(thread9, &fds);
	pthread_join(thread0, &fds);
	pthread_mutex_destroy(&cadeado);
	return (0);
}
