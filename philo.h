/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:49:58 by prachman          #+#    #+#             */
/*   Updated: 2023/06/04 13:27:24 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define FORK "\033[1;33m[%lu ms] philo %d is holding a fork\033[0m\n"
# define EAT "\033[1;32m[%lu ms] philo %d is eating\033[0m\n"
# define SLEEP "\033[1;34m[%lu ms] philo %d is sleeping\033[0m\n"
# define THINK "\033[1;38;5;208m[%lu ms] philo %d is thinking\033[0m\n"
# define DEAD "\033[1;31m[%lu ms] philo %d is dead\033[0m\n"

# define EXIT -1

typedef struct s_time
{
	long int	start;
	long int	die;
	long int	eat;
	long int	sleep;
	long int	max_meal;
}	t_time;

typedef struct s_alive
{
	int	is_dead;
}	t_alive;

typedef struct s_philo
{
	int				philo_id;
	int				meal;
	long int		hp;
	long int		rec;
	pthread_mutex_t	*lock;
	pthread_mutex_t	*mutex_l;
	pthread_mutex_t	*mutex_r;
	int				*fork_l;
	int				*fork_r;
	t_time			time;
	t_alive			*is_alive;
}	t_philo;

typedef struct s_var
{
	int					*fork;
	t_philo				*philo;
	t_alive				*is_alive;
	pthread_t			*th;
	pthread_mutex_t		*lock;
	pthread_mutex_t		*mutex;
}	t_var;

void		free_all(t_var *var, int size);
void		*routine(void *arg);
int			allocate(int size, t_var *var);
int			allocate_mutex(int size, t_var *var);
int			init_time(char **av, int ac, t_time *p_time);
void		init_fork(int size, t_var *var);
void		init_philo(int size, t_var *var, t_time time);
int			print_log(char *status, t_philo *philo);
int			ft_atoi(const char *str);
int			check_digit(char **av);
int			create_time(char **av, t_time *p_time);
long int	get_time(void);

#endif