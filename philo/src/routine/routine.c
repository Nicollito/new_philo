/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/16 12:49:48 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
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

int	ft_usleep(unsigned int us, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;
	unsigned long	elapsed_us;

	elapsed_us = 0;
	gettimeofday(&start, NULL);
	while (1)
	{
		if (philo && (isdead(philo, &philo->death_mutex) != ALIVE))
			return (1);
		gettimeofday(&current, NULL);
		elapsed_us = (current.tv_sec - start.tv_sec) * 1000000 +
			(current.tv_usec - start.tv_usec);
		if ((long)(us - elapsed_us) <= 0)
			break ;
	}
	return (0);
}

static void	routine_one(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_mutex);
	*philo->fork = 0;
	pthread_mutex_unlock(philo->fork_mutex);
	print_log(get_timestamp(), philo->num, FORK, philo->printf_mutex);
	while (1)
	{
		if (isdead(philo, &philo->death_mutex) != ALIVE)
			return ;
	}
}

void	*routine(void *philo_ptr)
{
	t_data			data;
	t_philo			*philo;
	pthread_mutex_t *death_mutex;

	philo = (t_philo *)philo_ptr;
	data = *philo->data;
	death_mutex = &philo->death_mutex;
	pthread_mutex_lock(philo->start);
	pthread_mutex_unlock(philo->start);
	if (data.num_of_philo == 1)
	{
		routine_one(philo);
		return (NULL);
	}
	if (!philo->num % 2)
		ft_usleep(data.time_to_eat * 100, NULL);
	while (1)
	{
		if (isdead(philo, death_mutex) != ALIVE)
			return (NULL);
		think(philo);
		if (isdead(philo, death_mutex) != ALIVE)
			return (NULL);
		if (eat(philo, data) != ALIVE)
			return (NULL);
		if (isdead(philo, death_mutex) != ALIVE)
			return (NULL);
		if (ft_sleep(philo, data) != ALIVE)
			return (NULL);
	}
}
