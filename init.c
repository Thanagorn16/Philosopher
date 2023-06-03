/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:19:43 by prachman          #+#    #+#             */
/*   Updated: 2023/06/03 11:36:09 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_time(char **av, int ac, t_time *p_time)
{
	int i;
	struct timeval tv;

	p_time->die = ft_atoi(av[2]) * 1000;
	p_time->eat = ft_atoi(av[3]) * 1000;
	p_time->sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		p_time->max_meal = ft_atoi(av[5]);
	else
		p_time->max_meal = 0;
	if (gettimeofday(&tv, NULL)== 0)
		p_time->start = tv.tv_sec * 1000000 + tv.tv_usec;
	else
		return (1); //!out
	return (0);
}

void	init_fork(int size, t_var *var)
{
	int i;

	i = 0;
	while (i < size)
	{
		var->fork[i] = i + 1;
		// printf("fork [%d] is %d\n", i, var->fork[i]);
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (var->fork[i] % 2 == 0)
		{
			var->fork[i] = 0;
			// printf("fork [%d] : [%d] is even\n", i, var->fork[i]);
		}
		else
		{
			var->fork[i] = 1;
			// printf("fork [%d] : [%d] is odd\n", i, var->fork[i]);
		}
		i++;
	}
}

void    init_philo(int size, t_var *var, t_time time)
{
	int i;

	i = 0;
	while (i < size)
	{
		// printf("i:%d\n", i);
		var->philo[i].philo_id = i + 1;
		var->philo[i].meal = 0;
		// var->philo[i].is_alive = 1;
		// printf("11111111111\n");
		var->philo[i].is_alive = var->is_alive;
		// printf("222222\n");
		var->philo[i].time = time;
		var->philo[i].lock = &var->lock[i];
		var->philo[i].mutex_l = &var->mutex[i];
		var->philo[i].fork_l = &var->fork[i];
		// printf("philo[%d] with lef_fork:%d and mode:%d\n", var->philo[i].philo_id, i, var->fork[i]);
		if (i == 0)
		{
			var->philo[i].mutex_r = &var->mutex[size - (i + 1)];
			var->philo[i].fork_r = &var->fork[size - (i + 1)];
			// printf("philo[%d] with right_fork:%d and mode:%d\n", var->philo[i].philo_id, size - (i+1), var->fork[size - (i + 1)]);
		}
		else
		{
			// printf("in else\n");
			var->philo[i].mutex_r = &var->mutex[i - 1];
			var->philo[i].fork_r = &var->fork[i - 1];
			// printf("philo[%d] with right_fork:%d and mode:%d\n", var->philo[i].philo_id, i - 1, var->fork[i - 1]);
		}
		i++;
	}
	// exit(0);
}