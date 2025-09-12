/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/12 15:50:20 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <unistd.h>

static int	isdead(t_philo *philo, pthread_mutex_t *death_mutex)
{
	int	status;

	pthread_mutex_lock(death_mutex);
	status = philo->dead;
	pthread_mutex_unlock(death_mutex);
	return (status);
}

void	*routine(void *philo_ptr)
{
	t_philo			*philo;
	t_data			*data;
	pthread_mutex_t *death_mutex;

	philo = (t_philo *)philo_ptr;
	data = philo->data;
	death_mutex = &philo->death_mutex;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	if (philo->num % 2)
		usleep(data->time_to_eat * 100);
	while (1)
	{
		if (isdead(philo, death_mutex))
			return (NULL);
		think(philo);
		if (isdead(philo, death_mutex))
			return (NULL);
		eat(philo, data);
		if (isdead(philo, death_mutex))
			return (NULL);
		ft_sleep(philo, data);
	}
}
