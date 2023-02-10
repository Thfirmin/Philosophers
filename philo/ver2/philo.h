/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:06:54 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/09 23:39:57 by thfirmin         ###   ########.fr       */
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

// Typedefs & Structs
typedef pthread_mutex_t	mutex_t;

typedef struct s_data
{
	int					n_philo;
	time_t				t_die;
	time_t				t_eat;
	time_t				t_sleep;
	int					n_eat;
	time_t				start;
	int					sim;
	int					unic;
	mutex_t				*m_data;
	mutex_t				*m_philo;
	mutex_t				*fork;
}						t_data;

typedef struct s_philo
{
	pthread_t			id;
	int					nb;
	time_t				t_life;
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
time_t	ph_getinst(time_t start);
void	ph_stamperr(char *message);

// ph_strutils
int		ph_isposnumber(char *nbr);
void	ph_putstr_fd(char *str, int fd);
time_t	ph_atol(char *str);

// ph_datautils
t_data	*ph_initdata(int argc, char *argv[]);
void	ph_cleandata(t_data **data);

// ph_mutexutils
mutex_t	*ph_initmutex(void);
mutex_t	*ph_initfork(t_data *data);
void	ph_destroymutex(mutex_t **mtx);
void	ph_destroyfork(t_data *data, mutex_t **fork);


#endif
