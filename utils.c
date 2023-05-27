/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 14:35:47 by prachman          #+#    #+#             */
/*   Updated: 2023/05/27 13:17:49 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    freeAll(t_var *var, int size)
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

int    print_log(char *status, t_philo *philo)
{
    pthread_mutex_lock(philo->lock);
    if (philo->is_alive != 0)
    {
        printf(status, (get_time() - philo->time.start) / 1000, philo->philo_id);
        pthread_mutex_unlock(philo->lock);
        return (0);
    }
    pthread_mutex_unlock(philo->lock);
    return (-1);
}

// int    print_log(char *status, t_philo *philo)
// {
//     if (status == FORK) //more simpler in header file
//     {
//         printf(status, (get_time() - philo->time.start) / 1000, philo->philo_id);
//         printf("%ld philo[%d] is holding a fork\n", 
//             (get_time() - philo->time.start) / 1000, philo->philo_id);
//     }
//     else if (status == EAT)
//     {
//         printf("%ld philo[%d] is eating\n", 
//             (get_time() - philo->time.start) / 1000, philo->philo_id);
//     }
//     else if (status == SLEEP)
//     {
//         printf("%ld philo[%d] is sleeping\n", 
//             (get_time() - philo->time.start) / 1000, philo->philo_id);
//     }
//     else if (status == THINK)
//     {
//         printf("%ld philo[%d] is thinking\n", 
//             (get_time() - philo->time.start) / 1000, philo->philo_id);
//     }
//     else if (status == DEATH)
//     {
//         printf("%ld philo[%d] is death\n", 
//             (get_time() - philo->time.start) / 1000, philo->philo_id);
//     }
// }