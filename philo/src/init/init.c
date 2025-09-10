/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:21:56 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/10 17:48:39 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static void	fill_int(int i, int *fork, t_data *data, t_philo *philo)
{
	philo[i].num = i + 1;
	philo[i].nbr_of_eat = data->num_of_eat;
	philo[i].fork = &fork[i];
	if (i < data->num_of_philo - 1)
		philo[i].next_fork = &fork[i + 1];
	else
		philo[i].next_fork = &fork[0];
	philo[i].data = data;
}

t_philo	*init_philo(t_data *data)
{
	int				i;
	int				*fork;
	t_philo			*philo;

	i = 0;
	fork = malloc(sizeof(int) * data->num_of_philo);
	if (!fork)
		return (NULL);
	memset(fork, 1, sizeof(int) * data->num_of_philo);
	philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!philo)
	{
		free(fork);
		return (NULL);
	}
	memset(philo, 0, sizeof(t_philo) * data->num_of_philo);
	while (i < data->num_of_philo)
	{
		fill_int(i, fork, data, philo);
		// init les mutex
		i++;
	}
	return (philo);
}
