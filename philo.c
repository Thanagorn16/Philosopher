/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: truangsi <truangsi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:50:03 by prachman          #+#    #+#             */
/*   Updated: 2023/06/04 13:08:11 by truangsi         ###   ########.fr       */
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
			return (EXIT);
		}
		i++;
	}
	i = 0;
	while (i < size)
	{
		if (pthread_join(var->th[i], NULL) != 0)
		{
			free_all(var, size);
			return (EXIT);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		size;
	t_time	p_time;
	t_var	var;

	size = ft_atoi(av[1]);
	if (ac < 5 || ac > 6)
		return (0);
	if (check_digit(av) == EXIT)
		return (EXIT);
	if (init_time(av, ac, &p_time) == EXIT)
		return (EXIT);
	if (allocate(size, &var) == EXIT)
	{
		free_all(&var, size);
		return (EXIT);
	}
	init_fork(size, &var);
	init_philo(size, &var, p_time);
	if (create_thread(size, &var) == EXIT)
		return (EXIT);
	free_all(&var, size);
}
