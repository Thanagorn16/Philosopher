/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 09:26:07 by prachman          #+#    #+#             */
/*   Updated: 2023/05/21 11:28: by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->lock);
	if (philo->is_alive->is_dead == 0)
	{
		pthread_mutex_unlock(philo->lock);
		return (EXIT);
	}
	pthread_mutex_unlock(philo->lock);
	if (philo->hp < get_time())
	{
		pthread_mutex_lock(philo->lock);
		philo->is_alive->is_dead = 0;
		philo->rec = get_time();
		printf(DEAD, (philo->rec - philo->time.start) / 1000, philo->philo_id);
		pthread_mutex_unlock(philo->lock);
		return (EXIT);
	}
	return (0);
}

int	take_fork(pthread_mutex_t *mutex, t_philo *philo, int *fork, int mode)
{
	while (check_death(philo) == 0)
	{
		pthread_mutex_lock(mutex);
		if (*(fork) == mode)
		{
			pthread_mutex_unlock(mutex);
			if (print_log(FORK, philo) < 0)
				return (EXIT);
			return (0);
		}
		pthread_mutex_unlock(mutex);
		usleep(50);
	}
	return (EXIT);
}

int	is_eating(t_philo *philo)
{
	if (print_log(EAT, philo) < 0)
		return (-1);
	philo->hp = philo->rec + philo->time.die;
	while ((get_time() - philo->rec) < philo->time.eat)
	{
		if (check_death(philo) == EXIT)
			return (EXIT);
		usleep(50);
	}
	pthread_mutex_lock(philo->mutex_l);
	pthread_mutex_lock(philo->mutex_r);
	*(philo->fork_l) = 0;
	*(philo->fork_r) = 1;
	pthread_mutex_unlock(philo->mutex_l);
	pthread_mutex_unlock(philo->mutex_r);
	if (philo->time.max_meal > 0)
	{
		philo->meal++;
		if (philo->meal == philo->time.max_meal)
			return (EXIT);
	}
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	if (print_log(SLEEP, philo) == EXIT)
		return (EXIT);
	while ((get_time() - philo->rec) < philo->time.sleep)
	{
		if (check_death(philo) == EXIT)
			return (EXIT);
		usleep(50);
	}
	if (print_log(THINK, philo) == EXIT)
		return (EXIT);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->hp = philo->time.start + philo->time.die;
	while (check_death(philo) == 0)
	{
		if (take_fork(philo->mutex_l, philo, philo->fork_l, 1) == EXIT)
			break ;
		if (take_fork(philo->mutex_r, philo, philo->fork_r, 0) == EXIT)
			break ;
		if (is_eating(philo) == EXIT)
			break ;
		if (is_sleeping(philo) == EXIT)
			break ;
	}
	return (NULL);
}
