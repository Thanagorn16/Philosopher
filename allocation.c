/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:18:22 by prachman          #+#    #+#             */
/*   Updated: 2023/06/04 13:13:46 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocate_mutex(int size, t_var *var)
{
	int	i;

	i = 0;
	var->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	if (!var->mutex)
		return (EXIT);
	while (i < size)
	{
		pthread_mutex_init(&var->mutex[i], NULL);
		i++;
	}
	i = 0;
	var->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!var->lock)
		return (EXIT);
	pthread_mutex_init(var->lock, NULL);
	return (0);
}

int	allocate(int size, t_var *var)
{
	var->philo = (t_philo *)malloc(sizeof(t_philo) * size);
	if (!var->philo)
		return (EXIT);
	var->th = (pthread_t *)malloc(sizeof(pthread_t) * size);
	if (!var->th)
		return (EXIT);
	if (allocate_mutex(size, var) == EXIT)
		return (EXIT);
	var->fork = (int *)malloc(sizeof(int) * size);
	if (!var->fork)
		return (EXIT);
	var->is_alive = (t_alive *)malloc(sizeof(t_alive));
	if (!var->is_alive)
		return (EXIT);
	var->is_alive->is_dead = 1;
	return (0);
}
