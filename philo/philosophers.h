/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:16:04 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/22 18:55:44 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

// Structs
typedef struct	s_philo
{
	pthread_t	thrd_id;
	int			thrd_nb;
	int			time_to_eat;
	int			time_to_die;

}				t_philo;

typedef struct	s_row
{
	int	time_to_eat;
	int	time_to_die;
	int	time_to_sleep;
	int	eat_times;
}		s_row;

long int	philo_getinstant(void);

#endif
