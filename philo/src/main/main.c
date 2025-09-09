/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:19:09 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/09 10:54:16 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo.h"

int	main(int ac, char **av)
{
	t_data 	data;
	t_philo	*philo;

	if (parsing(ac, av, &data))
		return (1);
	philo = init_philo(&data);
	if (!philo)
		return (1);
	return (0);
}