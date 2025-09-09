/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:21:56 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/09 14:53:16 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	init_next_fork(int i, t_data *data, t_philo *philo)
{
	if (i != data->num_of_philo - 1)
	{
		philo[i].next_fork = philo[i + 1].fork;
		philo[i].next_fork_mutex = &philo[i + 1].fork_mutex;
	}
	else
	{
		philo[i].next_fork = philo[0].fork;
		philo[i].next_fork_mutex = &philo[0].fork_mutex;
	}
}

t_philo	*init_philo(t_data *data)
{
	int				i;
	int				fork;
	t_philo			*philo;
	pthread_mutex_t	printf_mutex;
	pthread_mutex_t	death_mutex;

	i = 0;
	fork = 1;
	philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!philo)
		return (NULL);
	pthread_mutex_init(&printf_mutex, NULL);
	pthread_mutex_init(&death_mutex, NULL);
	while (i < data->num_of_philo)
	{
		philo[i].num = i + 1;
		philo[i].nbr_of_eat = data->num_of_eat;
		philo[i].data = data;
		philo[i].fork = &fork;
		pthread_mutex_init(&philo[i].fork_mutex, NULL);
		init_next_fork(i, data, philo);
		philo[i].printf_mutex = &printf_mutex;
		i++;
	}
	return (philo);
}
