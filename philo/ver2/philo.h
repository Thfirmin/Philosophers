/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:06:54 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/09 01:43:47 by thfirmin         ###   ########.fr       */
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

// Structs
typedef struct s_data
{
	int					n_philo;
	unsigned long int	t_die;
	unsigned long int	t_eat;
	unsigned long int	t_sleep;
	int					n_eat;
	unsigned long int	start;
	int					sim;
	int					unic;
	pthread_mutex_t		*m_sim;
	pthread_mutex_t		*m_stat;
	pthread_mutex_t		*m_data;
	pthread_mutex_t		*fork;
}						t_data;

typedef struct s_philo
{
	pthread_t			id;
	int					nb;
	unsigned long int	t_life;
	unsigned char		stat;
	int					n_eat;
	t_data				*data;
}						t_philo;

// Enums
enum	e_status
{
	P_FORK1 = 0,
	P_FORK2 = 1,
	P_EAT = 2,
	P_SLEEP = 3,
	P_THINK = 4,
	P_DIE = 5,
	PHILO_THINK = 20,
};


// ph_stamp
unsigned long int	ph_getinst(unsigned long int start);
void				ph_stamperr(char *message);

// ph_strutils
int					ph_isposnumber(char *nbr);
void				ph_putstr_fd(char *str, int fd);

#endif
