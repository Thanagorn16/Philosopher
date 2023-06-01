/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:49:58 by prachman          #+#    #+#             */
/*   Updated: 2023/05/31 22:18:25 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "\033[0;33m[%lu ms] philo %d is holding a fork\n" 
# define EAT "\033[0;32m[%lu ms] philo %d is eating\n"
# define SLEEP "\033[0;37m[%lu ms] philo %d is sleeping\n"
# define THINK "\033[0;34m[%lu ms] philo %d is thinking\n"
# define DEAD "\033[0;31m[%lu ms] philo %d is dead\n"

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
	long int        rec;
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
int 		allocate(int size, t_var *var);
int 		allocate_mutex(int size, t_var *var);
int 		init_time(char **av, t_time *p_time);
void    	init_fork(int size, t_var *var);
void    	init_philo(int size, t_var *var, t_time time);
int			print_log(char *status, t_philo *philo);
int			ft_atoi(const char *str);
int			check_digit(char **av);
int			create_time(char **av, t_time *p_time);
long int	get_time();

#endif