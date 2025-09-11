/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:19 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/11 16:41:30 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include <unistd.h>

void	ft_sleep(t_philo *philo)
{
	int	timestamp;

	timestamp = get_timestamp();
	pthread_mutex_lock(philo->printf_mutex);
	print_log(timestamp, philo->num, SLEEP);
	pthread_mutex_unlock(philo->printf_mutex);
	usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	int	timestamp;

	timestamp = get_timestamp();
	pthread_mutex_lock(philo->printf_mutex);
	print_log(timestamp, philo->num, THINK);
	pthread_mutex_unlock(philo->printf_mutex);
}

static int	action_on_fork(int *fork, int *next_fork, t_action action)
{
	if (action == TAKE)
	{
		if (*fork && *next_fork)
		{
			*fork = 0;
			*next_fork = 0;
			return (0);
		}
	}
	if (action == DEPOSIT)
	{
		if (!*fork && !*next_fork)
		{
			*fork = 1;
			*next_fork = 1;
			return (0);
		}
	}
	return (1);
}

void	use_fork(t_philo *philo, t_action action)
{
	int	return_value;

	return_value = 0;
	while (!return_value)
	{
		if (philo->num % 2)
		{
			pthread_mutex_lock(philo->fork_mutex);
			pthread_mutex_lock(philo->next_fork_mutex);
		}
		else
		{
			pthread_mutex_lock(philo->next_fork_mutex);
			pthread_mutex_lock(philo->fork_mutex);
		}
		return_value = action_on_fork(philo->fork, philo->next_fork, action);
		pthread_mutex_unlock(philo->fork_mutex);
		pthread_mutex_unlock(philo->next_fork_mutex);
	}
}

void	eat(t_philo *philo)
{
	int	timestamp;

	timestamp = get_timestamp();
	use_fork(philo, TAKE);
	pthread_mutex_lock(philo->printf_mutex);
	print_log(timestamp, philo->num, EAT);
	pthread_mutex_unlock(philo->printf_mutex);
	philo->last_meal = timestamp;
	usleep(philo->data->time_to_eat * 1000);
	use_fork(philo, DEPOSIT);
}
