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

        // if (philo->hp > call_time() - philo->time.start)
        // {
        //     printf("%ld philo[%d] is eating\n", 
        //         (call_time() - philo->time.start) / 1000, philo->phio_id);
        //     // while (call_time() - start_eat - philo->time.eat)
        //     // {
        //     //     // 
        //     //     usleep(50);
        //     // }
        //     printf("%ld philo[%d] is sleeping\n", 
        //         (call_time() - philo->time.start) / 1000, philo->phio_id);
        //     usleep(philo->time.sleep * 1000);
        //     printf("%ld philo[%d] is thinking\n", 
        //         (call_time() - philo->time.start) / 1000, philo->phio_id);
        // }
        // else
        // {
        //     printf("%ld philo[%d] is death\n",
        //         (call_time() - philo->time.start) / 1000, philo->phio_id);
        //     exit(0);
        // }

#include "philo.h"

int check_death(t_philo *philo)
{
    if (philo->hp < get_time())
    {
        pthread_mutex_lock(philo->lock);
        if (philo->is_alive == 0) //! kickout dead philo
        {
            pthread_mutex_unlock(philo->lock);
            return (-1);
        }
        philo->is_alive = 0;
        pthread_mutex_unlock(philo->lock);
        print_log(DEAD, philo);
        return (-1);
    }
    return (0); //not dead
}

int take_fork(pthread_mutex_t *mutex, t_philo *philo, int *fork, int mode)
{
    while (check_death(philo) == 0)
    {
        pthread_mutex_lock(mutex);
        if (fork = mode)
        {
            pthread_mutex_unlock(mutex);
            if (print_log(FORK, philo) < 0)
                return (-1);
            return (0);
        }
        pthread_mutex_unlock(mutex);
        usleep(50);
    }
    return (-1);
}

void    is_eating()
{
    // if (philo->hp > call_time() - philo->time.start)
    // {
    //     printf("%ld philo[%d] is eating\n", 
    //         (call_time() - philo->time.start) / 1000, philo->phio_id);
        // while (call_time() - start_eat - philo->time.eat)
        // {
        //     // 
        //     usleep(50);
        // }
}

void    is_sleeping()
{
    // printf("%ld philo[%d] is sleeping\n", 
    //     (call_time() - philo->time.start) / 1000, philo->phio_id);
    // usleep(philo->time.sleep * 1000);
    // printf("%ld philo[%d] is thinking\n", 
    //     (call_time() - philo->time.start) / 1000, philo->phio_id);
}

void    *routine(void *arg)
{
    t_philo     *philo;
    long int    start_eat;

    philo = (t_philo *)arg;
    philo->hp = philo->time.start + philo->time.die;
    // printf("%ld", philo->hp);
    // printf("philo: %d entered routine\n", philo->philo_id);
    while (check_death(philo) == 0)
    {
        if (take_fork(philo->mutex_l, philo, philo->fork_l, 1) < 0)
            break ;
        if (take_fork(philo->mutex_l, philo, philo->fork_r, 0) < 0)
            break ;
        // printf("philo [%d] is done\n", philo->philo_id);
    }
    return (NULL);
}