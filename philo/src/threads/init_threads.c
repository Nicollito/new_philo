/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:17 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/11 17:24:45 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_threads.h"
#include <stdlib.h>

int	init_threads(t_data *data, t_philo *philo)
{
	int			i;

	i = -1;
	pthread_mutex_lock(philo->start);
	while (++i < data->num_of_philo)
		pthread_create(&philo[i].threads, NULL, routine, &philo[i]);
	pthread_mutex_unlock(philo->start);
	return (0);
}
