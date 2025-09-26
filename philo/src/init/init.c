/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:21:56 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/26 18:32:18 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "parsing.h"
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

static int	init_mutex(int i, t_mutex *mutex, t_philo *philo)
{
	philo[i].fork_mutex = &mutex->fork[i];
	if (i < philo->data->num_of_philo - 1)
		philo[i].next_fork_mutex = &mutex->fork[i + 1];
	else
		philo[i].next_fork_mutex = &mutex->fork[0];
	philo[i].printf_mutex = mutex->printf;
	if (pthread_mutex_init(&philo[i].last_meal_mutex, NULL))
		return (1);
	if (pthread_mutex_init(philo[i].fork_mutex, NULL))
	{
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		return (1);
	}
	if (pthread_mutex_init(&philo[i].death_mutex, NULL))
	{
		pthread_mutex_destroy(&philo[i].last_meal_mutex);
		pthread_mutex_destroy(philo[i].fork_mutex);
		return (1);
	}
	return (0);
}

static void	destroy_philo_mutex(t_philo *philo)
{
	pthread_mutex_destroy(&philo->last_meal_mutex);
	pthread_mutex_destroy(philo->fork_mutex);
	pthread_mutex_destroy(&philo->death_mutex);
}

static int	init_loop(t_philo *philo, t_data *data, t_mutex *mutex, int *fork)
{
	int	i;

	i = -1;
	while (++i < data->num_of_philo)
	{
		init_int(i, fork, data, philo);
		if (init_mutex(i, mutex, philo))
		{
			ft_putendl("Error: Failed to initialize mutex", 2);
			while (i)
				destroy_philo_mutex(&philo[--i]);
			free(fork);
			free(philo);
			return (1);
		}
	}
	return (0);
}

t_philo	*init_philo(t_data *data)
{
	int				*fork;
	t_philo			*philo;
	t_mutex			mutex;

	if (malloc_table(&fork, &philo, data))
		return (NULL);
	if (malloc_mutex(&mutex, data))
	{
		free(fork);
		free(philo);
		return (NULL);
	}
	if (init_loop(philo, data, &mutex, fork))
		return (NULL);
	return (philo);
}
