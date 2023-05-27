/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:05 by prachman          #+#    #+#             */
/*   Updated: 2023/05/23 20:52:02 by prachman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    check_digit(char **av)
{
    // check if args are digit & not nev
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][j] < '0' || av[i][j] > '9')       
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

long int get_time()
{
    struct timeval tv;
    
    if (gettimeofday(&tv, NULL) != 0) //? correct way to do this?
        return (0); //!out
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}

int create_time(char **av, t_time *p_time)
{
    int i;
    struct timeval tv;
    
    i = 2;
    while (av[i])
    {
        if (i == 2)
            p_time->die =  ft_atoi(av[2]);
        if (i == 3)
            p_time->eat =  ft_atoi(av[3]);
        if (i == 4)
            p_time->sleep =  ft_atoi(av[4]);
        if (i == 5)
            p_time->max_meal =  ft_atoi(av[5]);
        i++;   
    }
    if (gettimeofday(&tv, NULL)== 0) //? correct way to do this?
        p_time->start = tv.tv_sec * 1000000 + tv.tv_usec;
    else
        return (1); //!out
    return (0);
}