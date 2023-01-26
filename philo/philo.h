/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thfirmin <thfirmin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:16:04 by thfirmin          #+#    #+#             */
/*   Updated: 2023/01/26 16:38:20 by thfirmin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

// Structs
typedef struct	s_philo
{
	pthread_t	id;
	int			nb;
	int			eat_nb;
	int			eat;
	int			die;
	int			sleep;
}				t_philo;

typedef struct	s_law
{
	int		philo_nbr;
	int		t_eat;
	int		t_die;
	int		t_sleep;
	int		eat_nbr;
	char	*forks;
}		t_law;

// Str Utils
void		philo_putstr_fd(char *str, int fd);
int			philo_atoi(char	*ascii);
int			philo_strlen(char *str);

// Struct Utils
void		philo_join(t_philo *philo, t_law *law)
t_philo		*philo_initphilo(t_law *law);
t_law		philo_initlaw(int argc, char *argv[]);


// Main
void		*philo_routine(void	*data);
long int	philo_getinstant(void);

#endif
