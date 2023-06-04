/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:18:22 by prachman          #+#    #+#             */
/*   Updated: 2023/06/04 11:30:07 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int allocate_mutex(int size, t_var *var)
{
	int i;

	i = 0;
	var->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
	if (!var->mutex)
		return (-1);
	while (i < size) //init mutex
	{
		pthread_mutex_init(&var->mutex[i], NULL);
		i++;
	}
	i = 0;
	var->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (!var->lock)
		return (-1);
	pthread_mutex_init(var->lock, NULL);
	return (0);
}

int allocate(int size, t_var *var)
{
	var->philo = (t_philo *)malloc(sizeof(t_philo) * size);
	if (!var->philo)
		return (0);
	var->th = (pthread_t *)malloc(sizeof(pthread_t) * size);
	if (!var->th)
		return (0);
	if (allocate_mutex(size, var) < 0)
		return (-1);
	var->fork = (int *)malloc(sizeof(int) * size);
	if (!var->fork)
		return (0);
	var->is_alive = (t_alive *)malloc(sizeof(t_alive));
	if (!var->is_alive)
		return (0);
	var->is_alive->is_dead = 1;
	return (1);
}