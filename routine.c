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

int check_death(t_philo *philo)
{
	// printf("index out:  %d\n", philo->philo_id);
	// printf("hp out:     %ld\n", philo->hp);
	// printf("time out:   %ld\n", get_time());
	pthread_mutex_lock(philo->lock);
	if (philo->is_alive->is_dead == 0) //! check if there's dead philo
	{
		pthread_mutex_unlock(philo->lock);
		return (EXIT);
	}
	pthread_mutex_unlock(philo->lock);
	if (philo->hp < get_time())
	{
		pthread_mutex_lock(philo->lock);
		// printf("index:  %d\n", philo->philo_id);
		// printf("hp:     %ld\n", philo->hp);
		// printf("time:   %ld\n", get_time());

		// if (philo->is_alive->is_dead == 0) //! kickout dead philo
		// {
		// 	pthread_mutex_unlock(philo->lock);
		// 	return (-1);
		// }

		philo->is_alive->is_dead = 0;
		philo->rec = get_time();
		printf(DEAD, (philo->rec - philo->time.start) / 1000, philo->philo_id); //considering change status to DEATH
		pthread_mutex_unlock(philo->lock);
		// print_log(DEAD, philo);
		return (EXIT);
		// if (print_log(DEAD, philo) < 0)
		//     return (-1);
	}
	return (0); //not dead
}

int take_fork(pthread_mutex_t *mutex, t_philo *philo, int *fork, int mode)
{
	// printf("fork:%d\n", *(fork));
	// printf("philo: %d | fork_mode:%d\n",philo->philo_id, *(fork));
	while (check_death(philo) == 0)
	{
		pthread_mutex_lock(mutex);
		if (*(fork) == mode)
		{
			// printf("philo: %d | fork_mode:%d\n",philo->philo_id, *(fork));
			pthread_mutex_unlock(mutex);
			if (print_log(FORK, philo) < 0)
				return (EXIT);
			return (0);
		}
		pthread_mutex_unlock(mutex);
		usleep(50);
	}
	// printf("222222222\n");
	return (EXIT);
}

int is_eating(t_philo *philo)
{
	if (print_log(EAT, philo) < 0)// eat
		return (-1);
	philo->hp = philo->rec + philo->time.die; // new hp
	// printf("eat_t:%ld\n", philo->time.eat);
	while ((get_time() - philo->rec) < philo->time.eat) // keep eating until reaching time.eat
	{
		// printf("HERE:%ld\n", get_time() - philo->rec);
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

int is_sleeping(t_philo *philo)
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

void    *routine(void *arg)
{
	t_philo     *philo;

	philo = (t_philo *)arg;
	philo->hp = philo->time.start + philo->time.die;
	// printf("%ld\n", philo->time.start);
	// return (NULL);
	// printf("%ld\n", philo->hp);
	// printf("philo: %d entered routine\n", philo->philo_id);
	while (check_death(philo) == 0)
	{
		if (take_fork(philo->mutex_l, philo, philo->fork_l, 1) == EXIT)
		{
			// printf("11111111\n");
			break ;
		}
		// printf("DONE TAKE LEFT FORK\n");
		if (take_fork(philo->mutex_r, philo, philo->fork_r, 0) == EXIT)
		{
			// printf("222222\n");
			break ;
		}
		// printf("DONE TAKE RIGHT FORK\n");
		if (is_eating(philo) == EXIT)
			break ;
		// printf("DONE EATING\n");
		if (is_sleeping(philo) == EXIT)
			break ;
		// printf("DONE SLEEPING/THINKING\n");
		// printf("philo [%d] is done\n", philo->philo_id);
	}
	return (NULL);
}