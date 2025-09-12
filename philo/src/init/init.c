/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:21:56 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/12 15:46:52 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include <string.h>
#include <stdlib.h>

static void	init_int(int i, int *fork, t_data *data, t_philo *philo)
{
	philo[i].num = i + 1;
	philo[i].nbr_of_eat = data->num_of_eat;
	philo[i].fork = &fork[i];
	if (i < data->num_of_philo - 1)
		philo[i].next_fork = &fork[i + 1];
	else
		philo[i].next_fork = &fork[0];
	philo[i].data = data;
}

static void	init_mutex(int i, t_mutex *mutex, t_philo *philo)
{
	pthread_mutex_init(&philo[i].last_meal_mutex, NULL);
	philo[i].fork_mutex = &mutex->fork[i];
	pthread_mutex_init(philo[i].fork_mutex, NULL);
	if (i < philo->data->num_of_philo - 1)
		philo[i].next_fork_mutex = &mutex->fork[i + 1];
	else
		philo[i].next_fork_mutex = &mutex->fork[0];
	philo[i].printf_mutex = mutex->printf;
	pthread_mutex_init(philo[i].printf_mutex, NULL);
	pthread_mutex_init(&philo[i].death_mutex, NULL);
	philo[i].start = mutex->start;
	pthread_mutex_init(philo[i].start, NULL);
}

t_philo	*init_philo(t_data *data)
{
	int				i;
	int				*fork;
	t_philo			*philo;
	t_mutex			mutex;

	i = 0;
	if (malloc_table(&fork, &philo, data))
		return (NULL);
	if (malloc_mutex(&mutex, data))
	{
		free(fork);
		free(philo);
		return (NULL);
	}
	while (i < data->num_of_philo)
	{
		init_int(i, fork, data, philo);
		init_mutex(i, &mutex, philo);
		i++;
	}
	return (philo);
}
