/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:17 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/17 18:28:53 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_threads.h"
#include "routine.h"

static void	init_threads(t_data *data, t_philo *philo)
{
	int			i;

	i = -1;
	pthread_mutex_lock(philo->start);
	while (++i < data->num_of_philo)
		pthread_create(&philo[i].threads, NULL, routine, &philo[i]);
	ft_usleep(data->num_of_philo * 1000, NULL);
	get_timestamp();
	pthread_mutex_unlock(philo->start);
}

static void	join_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->num_of_philo)
		pthread_join(philo[i].threads, NULL);
}

void	manage_threads(t_data *data, t_philo *philo)
{
	init_threads(data, philo);
	look_for_die(data, philo);
	join_threads(philo);
}
