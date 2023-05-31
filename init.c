/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:19:43 by prachman          #+#    #+#             */
/*   Updated: 2023/05/31 16:21:28 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_time(char **av, t_time *p_time)
{
    int i;
    struct timeval tv;
    
    i = 2;
    while (av[i])
    {
        if (i == 2)
            p_time->die =  ft_atoi(av[2]) * 1000;
        if (i == 3)
            p_time->eat =  ft_atoi(av[3]) * 1000;
        if (i == 4)
            p_time->sleep =  ft_atoi(av[4]) * 1000;
        if (i == 5)
            p_time->max_meal =  ft_atoi(av[5]) * 1000;
        i++;   
    }
    if (gettimeofday(&tv, NULL)== 0) //? correct way to do this?
        p_time->start = tv.tv_sec * 1000000 + tv.tv_usec;
    else
        return (1); //!out
    return (0);
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
        // printf("philo[%d] with lef_fork:%d and mode:%d\n", var->philo[i].philo_id, i, var->fork[i]);
        var->philo[i].mutex_r = &var->mutex[size - (i + 1)];
        var->philo[i].fork_r = &var->fork[size - (i + 1)];
        // printf("philo[%d] with right_fork:%d and mode:%d\n", var->philo[i].philo_id, size - (i+1), var->fork[size - (i + 1)]);
        i++;
    }
    // exit(0);
}