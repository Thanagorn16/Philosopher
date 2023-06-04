/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:35:47 by prachman          #+#    #+#             */
/*   Updated: 2023/06/04 13:15:42 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_var *var, int size)
{
	int	i;

	i = 0;
	free(var->philo);
	free(var->th);
	free(var->fork);
	free(var->is_alive);
	while (i < size)
		pthread_mutex_destroy(&var->mutex[i++]);
	free(var->mutex);
	pthread_mutex_destroy(var->lock);
	free(var->lock);
}

int	print_log(char *status, t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (philo->is_alive->is_dead > 0)
	{
		philo->rec = get_time();
		printf(status,
			(philo->rec - philo->time.start) / 1000, philo->philo_id);
		pthread_mutex_unlock(philo->lock);
		return (0);
	}
	pthread_mutex_unlock(philo->lock);
	return (EXIT);
}
