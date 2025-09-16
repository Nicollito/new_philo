/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:19 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/16 02:20:10 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include <unistd.h>
#include <stdio.h> //a del

int	ft_sleep(t_philo *philo, t_data data)
{
	int	timestamp;

	timestamp = get_timestamp();
	print_log(timestamp, philo->num, SLEEP, philo->printf_mutex);
	return (ft_msleep(data.time_to_sleep, philo));
}

void	think(t_philo *philo)
{
	int	timestamp;

	timestamp = get_timestamp();
	print_log(timestamp, philo->num, THINK, philo->printf_mutex);
}

static int	action_on_fork(int *fork, t_action action)
{
	if (action == TAKE && *fork)
	{
		*fork = 0;
		return (1);
	}
	if (action == DEPOSIT && !*fork)
	{
		*fork = 1;
		return (1);
	}
	return (0);
}
static void	take_first_fork(int *fork, pthread_mutex_t *mutex,
		t_action action)
{
	while (1)
	{
		pthread_mutex_lock(mutex);
		if (action_on_fork(fork, action))
			break ;
		pthread_mutex_unlock(mutex);
	}
	pthread_mutex_unlock(mutex);
}

static int	take_second_fork(int *fork, pthread_mutex_t *mutex,
		t_action action)
{
	int	status;

	pthread_mutex_lock(mutex);
	status = action_on_fork(fork, action);
	pthread_mutex_unlock(mutex);
	return (status);
}

static void	hunger_priority(t_philo *philo)
{
	int		time_since_meal;
	int		max_wait;
	int		wait_time;
	float	hunger_ration;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_meal = get_timestamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	hunger_ration = (float)time_since_meal / philo->data->time_to_die;
	max_wait = 5000;
	wait_time = max_wait * (1.0 - hunger_ration);
	fprintf(stderr, "wait_time [%d] [%d]\n", wait_time, philo->num);
	if (wait_time < 0)
		wait_time = 0;
	if (wait_time > max_wait)
		wait_time = max_wait;
	if (wait_time > 0)
		usleep(wait_time);
}

void	use_fork(t_philo *philo, t_action action)
{
	int	status;

	while (1)
	{
		hunger_priority(philo); //nul ça casse tout
		if (philo->num == philo->data->num_of_philo)
		{
			take_first_fork(philo->fork, philo->fork_mutex, action);
			status = take_second_fork(philo->next_fork, philo->next_fork_mutex, action);
			if (!status)
				take_first_fork(philo->fork, philo->fork_mutex, DEPOSIT);
		}
		else
		{
			take_first_fork(philo->next_fork, philo->next_fork_mutex, action);
			status = take_second_fork(philo->fork,  philo->fork_mutex, action);
			if (!status)
				take_first_fork(philo->next_fork, philo->next_fork_mutex, DEPOSIT);
		}
		if (status)
			break ;
	}
	if (action == TAKE)
	{
		print_log(get_timestamp(), philo->num, FORK, philo->printf_mutex);
		print_log(get_timestamp(), philo->num, FORK, philo->printf_mutex);
	}
}

int	eat(t_philo *philo, t_data data)
{
	int				timestamp;
	int				status;
	pthread_mutex_t	*last_meal_mutex;

	last_meal_mutex = &philo->last_meal_mutex;
	use_fork(philo, TAKE);
	timestamp = get_timestamp();
	if (isdead(philo, &philo->death_mutex))
	{
		use_fork(philo, DEPOSIT);
		return (1);
	}
	print_log(timestamp, philo->num, EAT, philo->printf_mutex);
	pthread_mutex_lock(last_meal_mutex);
	philo->last_meal = timestamp;
	pthread_mutex_unlock(last_meal_mutex);
	status = ft_msleep(data.time_to_eat, philo);
	use_fork(philo, DEPOSIT);
	return (status);
}
