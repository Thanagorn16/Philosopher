/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:35:47 by prachman          #+#    #+#             */
/*   Updated: 2023/06/03 13:47:27 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_var *var, int size)
{
	int i;

	i = 0;
	free(var->philo);
	free(var->th);
	free(var->fork);
	while (i < size)
		pthread_mutex_destroy(&var->mutex[i]);
	free(var->mutex);
}

int	print_log(char *status, t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (philo->is_alive->is_dead > 0) // check if note dead
	{
		philo->rec = get_time();
		printf(status, (philo->rec - philo->time.start) / 1000, philo->philo_id);
		pthread_mutex_unlock(philo->lock);
		return (0);
	}
	// else //!no need for this else?
	// {
	// 	philo->rec = get_time();
	// 	printf(DEAD, (philo->rec - philo->time.start) / 1000, philo->philo_id); //considering change status to DEATH
	// 	pthread_mutex_unlock(philo->lock);
	// 	return (-1);
	// }
	pthread_mutex_unlock(philo->lock);
	return (-1);
}