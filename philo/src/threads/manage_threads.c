/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:17 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/16 12:12:29 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_threads.h"
#include "routine.h"
#include <stdlib.h>

static void	set_state_philo(t_philo *philo, t_state current)
{
	int	i;

	i = 0;
	while (i < philo->data->num_of_philo)
	{
		pthread_mutex_lock(&philo[i].death_mutex);
		philo[i].state = current;
		pthread_mutex_unlock(&philo[i].death_mutex);
		i++;
	}
}

static t_state	check_state(t_philo *current, t_data *data,
	t_philo *philo, int timestamp)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&current->last_meal_mutex);
	if (timestamp - current->last_meal >= data->time_to_die)
	{
		pthread_mutex_unlock(&current->last_meal_mutex);
		return (DEAD);
	}
	pthread_mutex_unlock(&current->last_meal_mutex);
	if (data->num_of_eat == -1)
		return (ALIVE);
	while (++i < data->num_of_philo)
	{
		pthread_mutex_lock(&philo[i].last_meal_mutex);
		if (philo[i].nbr_of_eat > 0)
		{
			pthread_mutex_unlock(&philo[i].last_meal_mutex);
			return (ALIVE);
		}
		pthread_mutex_unlock(&philo[i].last_meal_mutex);
	}
	return (FED);
}

static void	look_for_die(t_data *data, t_philo *philo)
{
	int		i;
	t_state	state;
	int		timestamp;

	i = 0;
	state = ALIVE;
	while (1)
	{
		timestamp = get_timestamp();
		state = check_state(&philo[i], data, philo, timestamp);
		if (state != ALIVE)
		{
			set_state_philo(philo, state);
			break ;
		}
		i++;
		if (i == data->num_of_philo)
			i = 0;
	}
	ft_usleep(1000, NULL);
	if (state == DEAD)
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
	ft_usleep(data->num_of_philo * 100, NULL);
	pthread_mutex_unlock(philo->start);
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
