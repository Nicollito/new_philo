/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:07:37 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/15 20:28:40 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	destroy_mutex_loop(t_philo philo)
{
	pthread_mutex_destroy(&philo.last_meal_mutex);
	pthread_mutex_destroy(&philo.death_mutex);
}

void	free_philo(t_philo *philo)
{
	int	i;
	
	i = -1;
	pthread_mutex_destroy(philo->printf_mutex);
	pthread_mutex_destroy(philo->start);
	pthread_mutex_destroy(philo->fork_mutex);
	free(philo->printf_mutex);
	free(philo->start);
	free(philo->fork);
	free(philo->fork_mutex);
	while (++i < philo->data->num_of_philo)
	{
		destroy_mutex_loop(philo[i]);
	}
	free(philo);
}
