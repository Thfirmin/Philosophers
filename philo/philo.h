/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 20:31:58 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/03 18:35:41 by thfirmin         ###   ########.fr       */
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
	unsigned long int	instant;
	int					sim;
	int					unic;
	pthread_mutex_t		*s_mtx;
	pthread_mutex_t		*fork;
}						t_data;

typedef struct s_philo
{
	pthread_t			id;
	int					nb;
	unsigned long int	t_life;
	unsigned char		stat;
	pthread_mutex_t		*m_stat;
	int					n_eat;
	t_data				*data;
}						t_philo;

// Enums
enum	e_status
{
	M_FORK1 = 0,
	M_FORK2 = 1,
	M_EAT = 2,
	M_SLEEP = 3,
	M_THINK = 4,
	M_DIE = 5,
	PHILO_THINK = 20,
};

// philo
pthread_mutex_t		*philo_mtxinit(void);

// philo_stamp
void				philo_stamperr(char	*message);
unsigned long int	philo_getinst(void);
void				philo_stampmod(t_philo *philo, short mod);

// philo_strutils
int					philo_isposnumber(char *str);
void				philo_putstr_fd(char *str, int fd);
unsigned long int	philo_atol(char *str);

// philo_datautils
t_data				*philo_datainit(int argc, char *argv[]);
int					philo_datacheck(t_data *data);
void				philo_dataclean(t_data *data);

// philo_philoutils
t_philo				*philo_philoinit(t_data *data);
int					philo_philocheck(t_philo *philo);
void				philo_philoclean(t_philo *philo, t_data *data);

// philo_routine
void				*philo_routine(void *param);
void				philo_drop_fork(t_philo *philo);
void				philo_taketwo_fork(t_philo *philo);
void				philo_takeone_fork(t_philo *philo);
void				philo_die(t_philo *philo);

// philo_routineutils
void				philo_usleep(t_philo *philo, unsigned long int time);
void				philo_eat(t_philo *philo);
void				philo_sleep(t_philo *philo);
void				philo_think(t_philo *philo);
int					philo_islive(t_philo *philo);

// philo_mutex_utils
void				philo_write(void *dst, int src, pthread_mutex_t *mtx);
int					philo_read(int	dst, pthread_mutex_t *mtx);

#endif
