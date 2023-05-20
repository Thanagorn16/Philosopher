/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:03 by prachman          #+#    #+#             */
/*   Updated: 2023/05/20 14:01:44 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int allocate(char **av, t_var *var)
{
    int size;
    int i;

    size = ft_atoi(av[1]);
    var->philo = (t_philo *)malloc(sizeof(t_philo) * size);
    if (!var->philo)
        return (0);
    var->th = (pthread_t)malloc(sizeof(pthread_t) * size);
    if (!var->th)
        return (0);
    i = 0;
    var->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * size);
    if (!var->mutex)
        return (0);
    while (i < size)
    {
        pthread_mutex_init(&var->mutex[i], NULL);
        i++;
    }
    var->fork = (int *)malloc(sizeof(int) * size);
    if (!var->fork)
        return (0);
    return (1);
}

void    init_philo(int size, t_var *var, t_time time)
{
    int i;

    i = 0;
    while (i < size)
    {
        var->philo[i].phio_id = i + 1;
        var->philo[i].meal = 0;
        var->philo[i].hp = 1;
        var->philo[i].time = time;
        var->philo[i].mutex_l = &var->mutex[i];
        var->philo[i].fork_l = &var->fork[i];
        var->philo[i].mutex_r = &var->mutex[size - (i + 1)];
        var->philo[i].fork_r = &var->fork[size - (i + 1)];
        i++;
    }
}

int main(int ac, char **av)
{
    int i;
    int j;
    int size;
    char    num;
    t_time  p_time;
    t_var   var;

    if (ac < 5 || ac > 6)
        return (0);
    check_digit(av);
    create_time(av, &p_time);
    // allocate memories
    if (allocate(av, &var) != 1)
        return (0);
    size = ft_atoi(av[1]);
    init_philo(size, &var, p_time);
    i = 0;
    while (i < var.philo[i].phio_id)
        printf("hp%d\n", var.philo[i++].hp);
}