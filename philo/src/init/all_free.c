/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:07:37 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/26 18:24:15 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	destroy_mutex_loop(int i, t_philo *philo)
{
	pthread_mutex_destroy(&philo[i].last_meal_mutex);
	pthread_mutex_destroy(philo[i].fork_mutex);
	pthread_mutex_destroy(&philo[i].death_mutex);
}

void	free_philo(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->num_of_philo)
		destroy_mutex_loop(i, philo);
	pthread_mutex_destroy(philo->printf_mutex);
	pthread_mutex_destroy(&philo->data->start->ready_mutex);
	pthread_mutex_destroy(&philo->data->start->start_mutex);
	free(philo->printf_mutex);
	free(philo->fork);
	free(philo->fork_mutex);
	free(philo);
}
