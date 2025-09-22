/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:19 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/19 11:27:46 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include <stdio.h>

void	print_log(int timestamp, int philo, char *msg, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%d %d %s\n", timestamp, philo, msg);
	pthread_mutex_unlock(mutex);
}

t_state	ft_sleep(t_philo *philo, t_data data)
{
	int	timestamp;

	timestamp = get_timestamp();
	print_log(timestamp, philo->num, SLEEP, philo->printf_mutex);
	return (ft_usleep(data.time_to_sleep * 1000, philo));
}

void	think(t_philo *philo, t_data data)
{
	int	timestamp;

	(void)data;
	timestamp = get_timestamp();
	print_log(timestamp, philo->num, THINK, philo->printf_mutex);
	if (get_timestamp() - philo->last_meal + data.time_to_eat < data.time_to_die)
		ft_usleep(philo->data->time_to_eat * 1000, NULL);
}

static t_state	use_fork(t_philo *philo, t_action action)
{
	t_state	state;

	state = left_handed_philo(philo, action);
	return (state);
}

t_state	eat(t_philo *philo, t_data data)
{
	int				timestamp;
	int				status;
	pthread_mutex_t	*last_meal_mutex;

	last_meal_mutex = &philo->last_meal_mutex;
	if (use_fork(philo, TAKE) != ALIVE)
		return (DEAD);
	timestamp = get_timestamp();
	if (isdead(philo, &philo->death_mutex) != ALIVE)
	{
		use_fork(philo, DEPOSIT);
		return (DEAD);
	}
	pthread_mutex_lock(last_meal_mutex);
	philo->last_meal = timestamp;
	if (philo->nbr_of_eat > 0)
		philo->nbr_of_eat--;
	pthread_mutex_unlock(last_meal_mutex);
	print_log(timestamp, philo->num, EAT, philo->printf_mutex);
	status = ft_usleep(data.time_to_eat * 1000, philo);
	use_fork(philo, DEPOSIT);
	return (status);
}
