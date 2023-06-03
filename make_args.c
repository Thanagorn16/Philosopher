/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:51:05 by prachman          #+#    #+#             */
/*   Updated: 2023/06/03 15:23:46 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_digit(char **av)
{
	int i;
	int j;

	i = 1;
	while (av[i] != NULL)
	{
		j = 0;
		if (ft_strlen(av[i]) == 0)
			return (-1);
		while (av[i][j] != '\0')
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (-1);
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