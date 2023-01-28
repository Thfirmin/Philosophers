/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:16:04 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/28 03:22:25 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Includes
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

// Defines
# ifndef PHILO_CONSTS
#  define PHILO_CONSTS
#  define PHILO_THINK 150
#  define M_FORK 1
#  define M_EAT 2
#  define M_SLEEP 3
#  define M_THINK 4
#  define M_DIE 5
#  define M_UFORK 6
# endif

// Structs
typedef struct	s_law
{
	int					philo_nbr;
	unsigned long int	t_eat;
	unsigned long int	t_die;
	unsigned long int	t_sleep;
	int					eat_nbr;
	long unsigned int	instant;
	int					sim;
	pthread_mutex_t		s_mtx;
	pthread_mutex_t		*fork;
}		t_law;

typedef struct	s_philo
{
	pthread_t			id;
	int					nb;
	int					eat_nb;
	unsigned long int	life;
	int					die;
	t_law				*law;
}				t_philo;

// Str Utils
void		philo_putstr_fd(char *str, int fd);
int			philo_atoi(char	*ascii);
int			philo_strlen(char *str);
void		philo_messagestamp(t_philo *philo, short mode, int life);

// Struct Utils
void		philo_join(t_philo *philo, t_law *law);
void		philo_detach(t_philo *philo, t_law *law);
t_philo		*philo_initphilo(t_law *law);
t_law		*philo_initlaw(int argc, char *argv[]);
void		philo_clean_data(t_law *law, t_philo *philo);

// Main
void		*philo_routine(void	*data);

// Getinstant
long int	philo_getinstant(void);

#endif
