/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/19 11:16:04 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"
#include <unistd.h>
#include <sys/time.h>

t_state	isdead(t_philo *philo, pthread_mutex_t *death_mutex)
{
	t_state	status;

	pthread_mutex_lock(death_mutex);
	status = philo->state;
	pthread_mutex_unlock(death_mutex);
	return (status);
}

t_state	ft_usleep(unsigned int us, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;
	unsigned long	elapsed_us;

	elapsed_us = 0;
	gettimeofday(&start, NULL);
	while (1)
	{
		if (philo && (isdead(philo, &philo->death_mutex) != ALIVE))
			return (DEAD);
		gettimeofday(&current, NULL);
		elapsed_us = (current.tv_sec - start.tv_sec) * 1000000
			+ (current.tv_usec - start.tv_usec);
		if ((long)(us - elapsed_us) <= 0)
			break ;
		usleep(700);
	}
	return (ALIVE);
}

static void	loop(t_philo *philo, t_data data, pthread_mutex_t *death_mutex)
{
	if (philo->num % 2 == 0)
		think(philo, data);
	while (1)
	{
		if (isdead(philo, death_mutex) != ALIVE)
			return ;
		if (eat(philo, data) != ALIVE)
			return ;
		if (isdead(philo, death_mutex) != ALIVE)
			return ;
		if (ft_sleep(philo, data) != ALIVE)
			return ;
		if (isdead(philo, death_mutex) != ALIVE)
			return ;
		think(philo, data);
		usleep(600);
	}
}

void	*routine(void *philo_ptr)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t	*death_mutex;

	philo = (t_philo *)philo_ptr;
	data = *philo->data;
	death_mutex = &philo->death_mutex;
	loop(philo, data, death_mutex);
	return (NULL);
}
