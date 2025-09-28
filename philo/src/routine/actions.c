/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:19 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/28 15:36:03 by nimadela         ###   ########.fr       */
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
	int		timestamp;
	t_state	state;

	timestamp = get_timestamp();
	print_log(timestamp, philo->num, SLEEP, philo->printf_mutex);
	state = ft_usleep(data.time_to_sleep * 1000, philo);
	return (state);
}

void	think(t_philo *philo, t_data data)
{
	int	timestamp;

	if (isdead(philo, &philo->death_mutex))
		return ;
	timestamp = get_timestamp();
	print_log(timestamp, philo->num, THINK, philo->printf_mutex);
	if (get_timestamp() - philo->last_meal + data.time_to_eat
		< data.time_to_die)
		ft_usleep(philo->data->time_to_eat * 1000, NULL);
}

t_state	eat(t_philo *philo, t_data data)
{
	int				timestamp;
	int				status;
	pthread_mutex_t	*last_meal_mutex;

	last_meal_mutex = &philo->last_meal_mutex;
	if (left_handed_philo(philo) != ALIVE)
		return (DEAD);
	timestamp = get_timestamp();
	if (isdead(philo, &philo->death_mutex) != ALIVE)
	{
		deposit_fork(philo);
		return (DEAD);
	}
	pthread_mutex_lock(last_meal_mutex);
	philo->last_meal = timestamp;
	if (philo->nbr_of_eat > 0)
		philo->nbr_of_eat--;
	pthread_mutex_unlock(last_meal_mutex);
	print_log(timestamp, philo->num, EAT, philo->printf_mutex);
	status = ft_usleep(data.time_to_eat * 1000, philo);
	deposit_fork(philo);
	return (status);
}
