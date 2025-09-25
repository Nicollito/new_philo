/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:41:37 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/19 12:13:16 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include <unistd.h>

static int	action_on_fork(int *fork, t_action action)
{
	if (action == TAKE && *fork)
	{
		*fork = 0;
		return (1);
	}
	if (action == DEPOSIT)
	{
		*fork = 1;
		return (1);
	}
	return (0);
}

static t_state	take_fork(int *fork, pthread_mutex_t *mutex, t_philo *philo)
{
	t_state	state;

	while (1)
	{
		pthread_mutex_lock(mutex);
		if (action_on_fork(fork, TAKE))
			break ;
		pthread_mutex_unlock(mutex);
		state = isdead(philo, &philo->death_mutex);
		if (state != ALIVE)
			return (state);
		usleep(600);
	}
	pthread_mutex_unlock(mutex);
	state = isdead(philo, &philo->death_mutex);
	if (state != ALIVE)
		return (state);
	print_log(get_timestamp(), philo->num, FORK, philo->printf_mutex);
	return (ALIVE);
}

void	deposit_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_mutex);
	action_on_fork(philo->fork, DEPOSIT);
	pthread_mutex_unlock(philo->fork_mutex);
	pthread_mutex_lock(philo->next_fork_mutex);
	action_on_fork(philo->next_fork, DEPOSIT);
	pthread_mutex_unlock(philo->next_fork_mutex);
}

t_state	left_handed_philo(t_philo *philo)
{
	t_state	state;

	if (philo->num == philo->data->num_of_philo)
	{
		take_fork(philo->next_fork, philo->next_fork_mutex, philo);
		state = take_fork(philo->fork, philo->fork_mutex, philo);
		if (state != ALIVE)
		{
			deposit_fork(philo);
			return (state);
		}
	}
	else
	{
		take_fork(philo->fork, philo->fork_mutex, philo);
		state = take_fork(philo->next_fork, philo->next_fork_mutex, philo);
		if (state != ALIVE)
		{
			deposit_fork(philo);
			return (state);
		}
	}
	return (ALIVE);
}
