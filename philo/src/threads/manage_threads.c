/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:17 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/12 15:49:09 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_threads.h"
#include "routine.h"
#include <stdlib.h>
#include <unistd.h>

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
			pthread_mutex_lock(&philo[i].death_mutex);
			philo[i].dead = die;
			pthread_mutex_unlock(&philo[i].death_mutex);
			break ;
		}
		i++;
		if (i == data->num_of_philo)
			i = 0;
	}
	print_log(timestamp, philo[i].num, DIE, philo->printf_mutex);
}

static void	init_threads(t_data *data, t_philo *philo)
{
	int			i;

	i = -1;
	pthread_mutex_lock(philo->start);
	while (++i < data->num_of_philo)
		pthread_create(&philo[i].threads, NULL, routine, &philo[i]);
	usleep(data->num_of_philo * 100);
	get_timestamp();
	pthread_mutex_unlock(philo->start);
}

void	manage_threads(t_data *data, t_philo *philo)
{
	init_threads(data, philo);
	look_for_die(data, philo);
}
