/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:03 by prachman          #+#    #+#             */
/*   Updated: 2023/05/27 13:07:45 by prachman         ###   ########.fr       */
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
    var->lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
    if (!var->lock)
        return (-1);
    while (i < size) //init mutex
    {
        pthread_mutex_init(&var->lock[i], NULL);
        i++;
    }
    return (0);
}

int allocate(int size, t_var *var)
{
    int i;

    var->philo = (t_philo *)malloc(sizeof(t_philo) * size);
    if (!var->philo)
        return (0);
    var->th = (pthread_t *)malloc(sizeof(pthread_t) * size);
    if (!var->th)
        return (0);
    if (allocate_mutex(size, var) < 0)
        return (-1);
    // i = 0;
    // var->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
    // if (!var->mutex)
    //     return (0);
    // while (i < size) //init mutex
    // {
    //     pthread_mutex_init(&var->mutex[i], NULL);
    //     i++;
    // }
    var->fork = (int *)malloc(sizeof(int) * size);
    if (!var->fork)
        return (0);
    return (1);
}

void    init_fork(int size, t_var *var)
{
    int i;

    i = 0;
    while (i < size)
    {
        var->fork[i] = i + 1;
        // printf("fork [%d] is %d\n", i, var->fork[i]);
        i++;
    }
    i = 0;
    while (i < size)
    {
        if (var->fork[i] % 2 == 0)
        {
            var->fork[i] = 0;
            // printf("fork [%d] : [%d] is even\n", i, var->fork[i]);
        }
        else
        {
            var->fork[i] = 1;
            // printf("fork [%d] : [%d] is odd\n", i, var->fork[i]);
        }
        i++;
    }
}

void    init_philo(int size, t_var *var, t_time time)
{
    int i;

    i = 0;
    while (i < size)
    {
        var->philo[i].philo_id = i + 1;
        var->philo[i].meal = 0;
        var->philo[i].is_alive = 1;
        var->philo[i].time = time;
        var->philo[i].lock = &var->lock[i];
        var->philo[i].mutex_l = &var->mutex[i];
        var->philo[i].fork_l = &var->fork[i];
        var->philo[i].mutex_r = &var->mutex[size - (i + 1)];
        var->philo[i].fork_r = &var->fork[size - (i + 1)];
        i++;
    }
}

int main(int ac, char **av)
{
    int     i;
    int     j;
    int     size;
    char    num;
    t_time  p_time;
    t_var   var;

    if (ac < 5 || ac > 6)
        return (0);
    check_digit(av);
    create_time(av, &p_time);
    // allocate memories
    size = ft_atoi(av[1]);
    if (allocate(size, &var) != 1)
        return (0);
    var.philo->philo_sz = size;
    init_fork(size, &var);
    init_philo(size, &var, p_time);
    exit(0);
    i = 0;
    // while (i < var.philo[i].phio_id)
    //     printf("hp%d\n", var.philo[i++].hp);

    // create threads
    while (i < size)
    {
        if (pthread_create(&var.th[i], NULL, &routine, &var.philo[i]) != 0)
        {
            freeAll(&var, size);
            return (0);
        }
        i++;
    }
    i = 0;
    while (i < size)
    {
        if (pthread_join(var.th[i], NULL) != 0)
        {
            freeAll(&var, size);
        }
        i++;
    }
}