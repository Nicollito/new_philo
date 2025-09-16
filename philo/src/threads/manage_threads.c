/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:17 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/15 21:32:30 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_threads.h"
#include "routine.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h> //a del

static void	set_death_philo(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_lock(&philo[i].death_mutex);
		philo[i].dead = 1;
		pthread_mutex_unlock(&philo[i].death_mutex);
		i++;
	}
}

static void	look_for_die(t_data *data, t_philo *philo)
{
	int	i;
	int	die;
	int	timestamp;

	i = 0;
	die = 0;
	while (1)
	{
		timestamp = get_timestamp();
		pthread_mutex_lock(&philo[i].last_meal_mutex);
		if (timestamp - philo[i].last_meal >= data->time_to_die)
			die = 1;
		pthread_mutex_unlock(&philo[i].last_meal_mutex);
		if (die)
		{
			set_death_philo(philo);
			break ;
		}
		i++;
		if (i == data->num_of_philo)
			i = 0;
	}
	usleep(100);
	print_log(timestamp, philo[i].num, DIE, philo->printf_mutex);
}

static void	init_threads(t_data *data, t_philo *philo)
{
	int			i;

	i = -1;
	pthread_mutex_lock(philo->start);
	get_timestamp();
	while (++i < data->num_of_philo)
		pthread_create(&philo[i].threads, NULL, routine, &philo[i]);
	ft_msleep(data->num_of_philo / 10, NULL);
	pthread_mutex_unlock(philo->start);
	fprintf(stderr, "timestamp [%d]\n", get_timestamp());
}

static void	join_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->num_of_philo)
		pthread_join(philo[i].threads, NULL);
}

void	manage_threads(t_data *data, t_philo *philo)
{
	init_threads(data, philo);
	look_for_die(data, philo);
	join_threads(philo);
}
