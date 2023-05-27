/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:49:58 by prachman          #+#    #+#             */
/*   Updated: 2023/05/27 13:29:38 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "%lu ms %d has take a fork\n"
# define EAT "%lu ms %d is eating\n"
# define SLEEP "%lu ms %d is sleeping\n"
# define THINK "%lu ms %d is thinking\n"
# define DEAD "%lu ms %d is dead\n"

typedef struct s_time 
{
	long int start;
	long int die;
	long int eat;
	long int sleep;
	long int max_meal;
}   t_time;

typedef struct s_philo
{
	int             philo_id;
	int             philo_sz;
	int             meal;
	int				is_alive;
	long int        hp;
	pthread_mutex_t *lock;
	pthread_mutex_t	*mutex_l;
	pthread_mutex_t *mutex_r;
	int             *fork_l;
	int             *fork_r;
	t_time          time;
}   t_philo;

typedef struct s_var
{
	int             	*fork;
	t_philo         	*philo;
	pthread_t       	*th;
	pthread_mutex_t 	*lock;
	pthread_mutex_t		*mutex;
}   t_var;

void    	freeAll(t_var *var, int size);
void    	*routine(void *arg);
int			print_log(char *status, t_philo *philo);
int			ft_atoi(const char *str);
int			check_digit(char **av);
int			create_time(char **av, t_time *p_time);
long int	get_time();

#endif