/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:41:37 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/17 17:20:57 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

int	action_on_fork(int *fork, t_action action)
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

void	take_first_fork(int *fork, pthread_mutex_t *mutex, t_action action)
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

int	take_second_fork(int *fork, pthread_mutex_t *mutex, t_action action)
{
	int	status;

	pthread_mutex_lock(mutex);
	status = action_on_fork(fork, action);
	pthread_mutex_unlock(mutex);
	return (status);
}

void	hunger_priority(t_philo *philo)
{
	int		time_since_meal;
	int		max_wait;
	int		wait_time;
	float	hunger_ration;

	pthread_mutex_lock(&philo->last_meal_mutex);
	time_since_meal = get_timestamp() - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	hunger_ration = (float)time_since_meal / philo->data->time_to_die;
	max_wait = 500;
	wait_time = max_wait * (1.0 - hunger_ration);
	if (wait_time < 0)
		wait_time = 0;
	if (wait_time > max_wait)
		wait_time = max_wait;
	if (wait_time > 0)
		ft_usleep(wait_time, NULL);
}

int	left_handed_philo(t_philo *philo, t_action action)
{
	int	status;

	if (philo->num == philo->data->num_of_philo)
	{
		take_first_fork(philo->fork, philo->fork_mutex, action);
		status = take_second_fork(philo->next_fork, philo->next_fork_mutex,
				action);
		if (!status)
			take_first_fork(philo->fork, philo->fork_mutex, DEPOSIT);
	}
	else
	{
		take_first_fork(philo->next_fork, philo->next_fork_mutex, action);
		status = take_second_fork(philo->fork, philo->fork_mutex, action);
		if (!status)
			take_first_fork(philo->next_fork, philo->next_fork_mutex, DEPOSIT);
	}
	return (status);
}
