/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:19:43 by prachman          #+#    #+#             */
/*   Updated: 2023/06/04 13:12:54 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(char **av, int ac, t_time *p_time)
{
	struct timeval	tv;

	p_time->die = ft_atoi(av[2]) * 1000;
	p_time->eat = ft_atoi(av[3]) * 1000;
	p_time->sleep = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		p_time->max_meal = ft_atoi(av[5]);
	else
		p_time->max_meal = 0;
	if (gettimeofday(&tv, NULL) == 0)
		p_time->start = tv.tv_sec * 1000000 + tv.tv_usec;
	else
		return (EXIT);
	return (0);
}

void	init_fork(int size, t_var *var)
{
	int	i;

	i = 0;
	while (i < size)
	{
		var->fork[i] = i + 1;
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (var->fork[i] % 2 == 0)
			var->fork[i] = 0;
		else
			var->fork[i] = 1;
		i++;
	}
}

void	init_philo(int size, t_var *var, t_time time)
{
	int	i;

	i = 0;
	while (i < size)
	{
		var->philo[i].philo_id = i + 1;
		var->philo[i].meal = 0;
		var->philo[i].is_alive = var->is_alive;
		var->philo[i].time = time;
		var->philo[i].lock = var->lock;
		var->philo[i].mutex_l = &var->mutex[i];
		var->philo[i].fork_l = &var->fork[i];
		if (i == 0)
		{
			var->philo[i].mutex_r = &var->mutex[size - (i + 1)];
			var->philo[i].fork_r = &var->fork[size - (i + 1)];
		}
		else
		{
			var->philo[i].mutex_r = &var->mutex[i - 1];
			var->philo[i].fork_r = &var->fork[i - 1];
		}
		i++;
	}
}
