/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prachman <prachman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:05 by prachman          #+#    #+#             */
/*   Updated: 2023/05/31 16:26:26 by prachman         ###   ########.fr       */
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
    
    if (gettimeofday(&tv, NULL) != 0)
        return (0); //!out
    return (tv.tv_sec * 1000000 + tv.tv_usec);
}