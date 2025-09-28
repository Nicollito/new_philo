/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:19:09 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/28 17:15:52 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		status;
	t_data	data;
	t_philo	*philo;

	if (parsing(ac, av, &data))
		return (1);
	philo = init_philo(&data);
	if (!philo)
		return (1);
	status = manage_threads(&data, philo);
	free_philo(philo);
	return (status);
}
