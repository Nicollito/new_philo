/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:19:09 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/17 17:18:13 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philo;

	if (parsing(ac, av, &data))
		return (1);
	philo = init_philo(&data);
	if (!philo)
		return (1);
	manage_threads(&data, philo);
	free_philo(philo);
	return (0);
}
