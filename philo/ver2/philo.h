/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 01:06:54 by thfirmin          #+#    #+#             */
/*   Updated: 2023/02/15 20:12:46 by thfirmin         ###   ########.fr       */
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
	int					n_philo; // RD
	time_t				t_die; // RD
	time_t				t_eat; // RD
	time_t				t_sleep; // RD
	int					n_eat; // RD
	time_t				start; // RD
	int					sim; // RDWR
	mutex_t				*m_data; // MTX
	mutex_t				*m_philo; // MTX
	mutex_t				**fork; // MTX
}						t_data;

typedef struct s_philo
{
	pthread_t			id; // RD
	int					nb; // RD
	time_t				t_life; // RDWR
	unsigned char		stat; // RDWR
	int					n_eat; // RDWR
	t_data				*data; // RDWR
}						t_philo;

// Enums
typedef enum e_status
{
	P_FORK1 = 0,
	P_FORK2 = 1,
	P_EAT = 2,
	P_SLEEP = 3,
	P_THINK = 4,
	P_DIE = 5,
	P_EATED = 6,
	T_THINK = 150,
}	t_status;


// ph_stamp
time_t	ph_getinst(time_t start);
void	ph_stamperr(char *message);
void	ph_stamplog(t_philo *ph, t_status stat);

// ph_strutils
int		ph_isposnumber(char *nbr);
void	ph_putstr_fd(char *str, int fd);
time_t	ph_atol(char *str);

// ph_datautils
t_data	*ph_initdata(int argc, char *argv[]);
int		ph_checkdata(t_data *data);
void	ph_cleandata(t_data **data);

// ph_philoutils
t_philo	*ph_initphilo(t_data *data);
int		ph_checkphilo(t_philo *philo, t_data *data);
void	ph_cleanphilo(t_philo **philo, t_data *data);

// ph_mutexutils
mutex_t	*ph_initmutex(void);
mutex_t	**ph_initfork(t_data *data);
void	ph_destroymutex(mutex_t **mtx);
void	ph_destroyfork(t_data *data, mutex_t ***fork);

// ph_routine
void	*ph_routine(void *param);
void	ph_eat(t_philo *ph);
void	ph_sleep(t_philo *ph);
void	ph_think(t_philo *ph);
void	ph_die(t_philo *ph);

// ph_routineutils
int		ph_islive(t_philo *ph);
void	ph_takeone_fork(t_philo *ph);
void	ph_taketwo_fork(t_philo *ph);
void	ph_dropfork(t_philo *ph);
void	ph_usleep(t_philo *ph, time_t t_mcs);

// ph_rdwr_data
void	ph_wrdt(t_philo *ph, void *data, int aux, short mod);
int		ph_rddt(t_philo *ph, void *data, int cmp);

// ph_rdwr_philo
int		ph_rdph_stat(t_philo *ph, t_status flag);
void	ph_wrph_stat(t_philo *ph, t_status flag, short mod);
int		ph_rdph(t_philo *ph, void *data);
void	ph_wrph(t_philo *ph, void *data, int aux, short mod);
time_t	ph_rdph_tlife(t_philo *ph);

#endif
