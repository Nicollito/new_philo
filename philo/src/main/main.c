/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:19:09 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/15 20:34:23 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	print_data(t_data *data)
{
	printf("num philo [%d]\n", data->num_of_philo);
	printf("time die  [%d]\n", data->time_to_die);
	printf("time eat  [%d]\n", data->time_to_eat);
	printf("time slp  [%d]\n", data->time_to_sleep);
	printf("num eat   [%d]\n", data->num_of_eat);
}

int	main(int ac, char **av)
{
	t_data 	data;
	t_philo	*philo;

	if (parsing(ac, av, &data))
		return (1);
	philo = init_philo(&data);
	if (!philo)
		return (1);
	manage_threads(&data, philo);
	free_philo(philo);
	return (0);
}
