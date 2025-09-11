/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 13:07:12 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/11 16:40:52 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include <stdlib.h>
#include <string.h>

int	malloc_table(int **fork, t_philo **philo, t_data *data)
{
	*fork = malloc(sizeof(int) * data->num_of_philo);
	if (!*fork)
		return (1);
	memset(*fork, 1, sizeof(int) * data->num_of_philo);
	*philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!*philo)
	{
		free(*fork);
		return (1);
	}
	memset(*philo, 0, sizeof(t_philo) * data->num_of_philo);
	return (0);
}

int	malloc_mutex(t_mutex *mutex, t_data *data)
{
	mutex->fork = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!mutex->fork)
		return (1);
	mutex->printf = malloc(sizeof(pthread_mutex_t));
	if (!mutex->fork)
	{
		free(mutex->fork);
		return (1);
	}
	mutex->death = malloc(sizeof(pthread_mutex_t));
	if (!mutex->death)
	{
		free(mutex->fork);
		free(mutex->printf);
		return (1);
	}
	mutex->start = malloc(sizeof(pthread_mutex_t));
	if (!mutex->start)
	{
		free(mutex->fork);
		free(mutex->printf);
		free(mutex->death);
		return (1);
	}
	return (0);
}
