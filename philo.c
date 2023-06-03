/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:03 by prachman          #+#    #+#             */
/*   Updated: 2023/06/03 15:23:39 by truangsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_thread(int size, t_var *var)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (pthread_create(&var->th[i], NULL, &routine, &var->philo[i]) != 0)
		{
			free_all(var, size);
			return (-1);
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (pthread_join(var->th[i], NULL) != 0)
		{
			free_all(var, size);
			return (-1);
		}
		i++;
	}
	return (0);
}

int main(int ac, char **av)
{
	int		size;
	t_time	p_time;
	t_var	var;

	if (ac < 5 || ac > 6)
		return (0);
	if (check_digit(av) < 0)
		return (-1);
	init_time(av, ac, &p_time);
	size = ft_atoi(av[1]);
	if (allocate(size, &var) != 1)
		return (0);
	init_fork(size, &var);
	init_philo(size, &var, p_time);
	create_thread(size, &var);
}
