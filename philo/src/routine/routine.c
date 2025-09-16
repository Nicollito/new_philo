/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/15 21:52:19 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "routine.h"
#include <unistd.h>
#include <sys/time.h>

int	isdead(t_philo *philo, pthread_mutex_t *death_mutex)
{
	int	status;

	pthread_mutex_lock(death_mutex);
	status = philo->dead;
	pthread_mutex_unlock(death_mutex);
	return (status);
}

int	ft_msleep(unsigned int ms, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;
	unsigned long	elapsed_us;

	ms *= 1000;
	elapsed_us = 0;
	gettimeofday(&start, NULL);
	while (1)
	{
		if (philo && isdead(philo, &philo->death_mutex))
			return (1);
		gettimeofday(&current, NULL);
		elapsed_us = (current.tv_sec - start.tv_sec) * 1000000 +
			(current.tv_usec - start.tv_usec);
		if ((long)(ms - elapsed_us) <= 0)
			break ;
	}
	return (0);
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
	if (philo->num % 2)
		ft_msleep(data.time_to_eat / 10, NULL);
	while (1)
	{
		if (isdead(philo, death_mutex))
			return (NULL);
		think(philo);
		if (isdead(philo, death_mutex))
			return (NULL);
		if (eat(philo, data))
			return (NULL);
		if (isdead(philo, death_mutex))
			return (NULL);
		if (ft_sleep(philo, data))
			return (NULL);
	}
}
