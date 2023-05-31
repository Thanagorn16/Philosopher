/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:03 by prachman          #+#    #+#             */
/*   Updated: 2023/05/31 16:26:10 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
    init_time(av, &p_time);
    // allocate memories
    size = ft_atoi(av[1]);
    if (allocate(size, &var) != 1)
        return (0);
    var.philo->philo_sz = size;
    init_fork(size, &var);
    init_philo(size, &var, p_time);
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