/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:43:17 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/19 12:08:13 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_threads.h"
#include "routine.h"

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
			if (!i)
				return (0);
			while (--i)
				pthread_join(philo[i].threads, NULL);
			return (0);
		}
	}
	return (1);
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
	int	status;

	status = init_threads(data, philo);
	if (status)
	{
		look_for_die(data, philo);
		join_threads(philo);
	}
}
