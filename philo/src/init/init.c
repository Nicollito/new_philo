/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:21:56 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/09 11:53:21 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static void	init_next_fork(int i, t_data *data, t_philo *philo)
{
	if (i != data->num_of_philo - 1)
	{
		philo[i].next_fork = philo[i + 1].fork;
		philo[i].next_f_mutex = &philo[i + 1].f_mutex;
	}
	else
	{
		philo[i].next_fork = philo[0].fork;
		philo[i].next_f_mutex = &philo[0].f_mutex;
	}
}

t_philo	*init_philo(t_data *data)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	printf_mutex;

	i = 0;
	philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!philo)
		return (NULL);
	pthread_mutex_init(&printf_mutex, NULL);
	while (i < data->num_of_philo)
	{
		philo[i].num = i + 1;
		philo[i].nbr_of_eat = data->num_of_eat;
		*philo[i].fork = 1;
		pthread_mutex_init(&philo[i].f_mutex, NULL);
		init_next_fork(i, data, philo);
		philo[i].printf_mutex = &printf_mutex;
		i++;
	}
	return (philo);
}
