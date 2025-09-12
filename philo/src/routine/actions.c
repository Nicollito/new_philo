/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:19 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/12 15:39:16 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include <unistd.h>

void	ft_sleep(t_philo *philo, t_data *data)
{
	int	timestamp;

	timestamp = get_timestamp();
	print_log(timestamp, philo->num, SLEEP, philo->printf_mutex);
	usleep((data->time_to_sleep * 1000));
}

void	think(t_philo *philo)
{
	int	timestamp;

	timestamp = get_timestamp();
	print_log(timestamp, philo->num, THINK, philo->printf_mutex);
}

static int	action_on_fork(int *fork, int *next_fork, t_action action,
	t_philo *philo)
{
	if (action == TAKE)
	{
		if (*fork && *next_fork)
		{
			*fork = 0;
			print_log(get_timestamp(), philo->num, FORK, philo->printf_mutex);
			*next_fork = 0;
			print_log(get_timestamp(), philo->num, FORK, philo->printf_mutex);
			return (1);
		}
	}
	if (action == DEPOSIT)
	{
		if (!*fork && !*next_fork)
		{
			*fork = 1;
			*next_fork = 1;
			return (1);
		}
	}
	return (0);
}

void	use_fork(t_philo *philo, t_action action)
{
	int				return_value;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*next_fork_mutex;

	return_value = 0;
	fork_mutex = philo->fork_mutex;
	next_fork_mutex = philo->next_fork_mutex;
	while (1)
	{
		if (philo->num % 2)
		{
			pthread_mutex_lock(fork_mutex);
			pthread_mutex_lock(next_fork_mutex);
		}
		else
		{
			pthread_mutex_lock(next_fork_mutex);
			pthread_mutex_lock(fork_mutex);
		}
		return_value = action_on_fork(philo->fork, philo->next_fork, action, philo);
		pthread_mutex_unlock(fork_mutex);
		pthread_mutex_unlock(next_fork_mutex);
		if (return_value)
			break ;
		// usleep(10);
	}
}

void	eat(t_philo *philo, t_data *data)
{
	int				timestamp;
	pthread_mutex_t	*last_meal_mutex;

	last_meal_mutex = &philo->last_meal_mutex;
	use_fork(philo, TAKE);
	timestamp = get_timestamp();
	print_log(timestamp, philo->num, EAT, philo->printf_mutex);
	pthread_mutex_lock(last_meal_mutex);
	philo->last_meal = timestamp;
	pthread_mutex_unlock(last_meal_mutex);
	usleep((data->time_to_eat * 1000));
	use_fork(philo, DEPOSIT);
}
