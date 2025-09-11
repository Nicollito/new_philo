/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/11 16:56:13 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <unistd.h>

void	*routine(void *philo_ptr)
{
	t_philo	*philo;

	philo = (t_philo *)philo_ptr;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	if (philo->num % 2)
		usleep(philo->data->time_to_eat * 100);
	while (1)
	{
		think(philo);
		eat(philo);
		ft_sleep(philo);
	}
}
