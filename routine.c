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
    // pthread_mutex_lock(philo->lock);
    // printf("index out:  %d\n", philo->philo_id);
    // printf("hp out:     %ld\n", philo->hp);
    // printf("time out:   %ld\n", get_time());
    // pthread_mutex_unlock(philo->lock);
    if (philo->hp < get_time())
    {
        pthread_mutex_lock(philo->lock);
        // printf("index:  %d\n", philo->philo_id);
        // printf("hp:     %ld\n", philo->hp);
        // printf("time:   %ld\n", get_time());
        if (philo->is_alive == 0) //! kickout dead philo
        {
            pthread_mutex_unlock(philo->lock);
            return (-1);
        }
        philo->is_alive = 0;
        pthread_mutex_unlock(philo->lock);
        print_log(DEAD, philo);
        return (-1);
        // if (print_log(DEAD, philo) < 0)
        //     return (-1);
    }
    return (0); //not dead
}

int take_fork(pthread_mutex_t *mutex, t_philo *philo, int *fork, int mode)
{
    // printf("fork:%d\n", *(fork));
    while (check_death(philo) == 0)
    {
        pthread_mutex_lock(mutex);
        if (*(fork) == mode)
        {
            // printf("philo: %d | fork_mode:%d\n",philo->philo_id, *(fork));
            pthread_mutex_unlock(mutex);
            if (print_log(FORK, philo) < 0)
                return (-1);
            return (0);
        }
        pthread_mutex_unlock(mutex);
        usleep(50);
    }
    // printf("222222222\n");
    return (-1);
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
        if (check_death(philo) < 0)
            return (-1);
        usleep(50);
    }
    pthread_mutex_lock(philo->mutex_l);
    pthread_mutex_lock(philo->mutex_r);
    *(philo->fork_l) = 0;
    *(philo->fork_r) = 1;
    pthread_mutex_unlock(philo->mutex_l);
    pthread_mutex_unlock(philo->mutex_r);
    return (0);
}

int is_sleeping(t_philo *philo)
{
    if (print_log(SLEEP, philo) < 0)
        return (-1);
    while ((get_time() - philo->rec) < philo->time.sleep)
    {
        if (check_death(philo) < 0)
            return (-1);
        usleep(50);
    }
    if (print_log(THINK, philo) < 0)
        return (-1);
    return (0);
}

void    *routine(void *arg)
{
    t_philo     *philo;
    long int    start_eat;

    philo = (t_philo *)arg;
    philo->hp = philo->time.start + philo->time.die;
    // printf("%ld\n", philo->hp);
    // printf("philo: %d entered routine\n", philo->philo_id);
    while (check_death(philo) == 0)
    {
        if (take_fork(philo->mutex_l, philo, philo->fork_l, 1) < 0)
            break ;
        // printf("DONE TAKE LEFT FORK\n");
        if (take_fork(philo->mutex_r, philo, philo->fork_r, 0) < 0)
        {
            // printf("111111111\n");
            break ;
        }
        // printf("DONE TAKE RIGHT FORK\n");
        if (is_eating(philo) < 0)
            break ;
        // printf("DONE EATING\n");
        if (is_sleeping(philo) < 0)
            break ;
        // printf("DONE SLEEPING/THINKING\n");
        // printf("philo [%d] is done\n", philo->philo_id);
    }
    return (NULL);
}