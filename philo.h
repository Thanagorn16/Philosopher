/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:49:58 by prachman          #+#    #+#             */
/*   Updated: 2023/05/20 14:01:23 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
// # include "libft/libft.h"

typedef struct s_time 
{
	int start;
	int die;
	int eat;
	int sleep;
	int max_meal;
}   t_time;

typedef struct s_philo
{
	int             phio_id;
	int             meal;
	int             hp;
	pthread_mutex_t *mutex_l;
	pthread_mutex_t *mutex_r;
	int             *fork_l;
	int             *fork_r;
	t_time          time;
}   t_philo;

typedef struct s_var
{
	int             	*fork;
	t_philo         	*philo;
	pthread_t       	th;
	pthread_mutex_t    *mutex;
}   t_var;

int	ft_atoi(const char *str);
int	check_digit(char **av);
int	create_time(char **av, t_time *p_time);

#endif