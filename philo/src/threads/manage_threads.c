/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:17 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/28 17:21:46 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_threads.h"
#include "routine.h"
#include "parsing.h"
#include <unistd.h>

/* static void	set_threads_ready(t_data *data, t_start *start)
{
	int	ready;

	while (1)
	{
		pthread_mutex_lock(&start->ready_mutex);
		ready = start->ready_count;
		pthread_mutex_unlock(&start->ready_mutex);
		if (ready == data->num_of_philo)
		{
			pthread_mutex_lock(&start->start_mutex);
			get_timestamp();
			start->start = READY;
			pthread_mutex_unlock(&start->start_mutex);
			break ;
		}
		usleep(100);
	}
} */

static int	init_threads(t_data *data, t_philo *philo)
{
	int			i;

	i = -1;
	get_timestamp();
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&philo[i].threads, NULL, routine, &philo[i]))
		{
			set_state_philo(philo, DEAD);
			ft_putendl("Error: Failed to create thread (pthread_create returned\
 an error).", 2);
			while (i)
				pthread_join(philo[--i].threads, NULL);
			return (1);
		}
	}
	return (0);
}

static void	join_threads(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->num_of_philo)
		pthread_join(philo[i].threads, NULL);
}

int	manage_threads(t_data *data, t_philo *philo)
{
	int	status;

	status = init_threads(data, philo);
	if (!status)
	{
		look_for_die(data, philo);
		join_threads(philo);
	}
	return (status);
}
