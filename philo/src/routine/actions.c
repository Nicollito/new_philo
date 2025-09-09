/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 15:32:19 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/09 15:42:35 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "routine.h"

void	think(t_philo philo)
{
	pthread_mutex_lock(philo.printf_mutex);
	print_log(get_timestamp, philo.num, THINK);
	pthread_mutex_unlock(philo.printf_mutex);
}

void	take_fork(t_philo philo)
{
	if (philo.num % 2)
	{
		pthread_mutex_lock(&philo.fork_mutex);
		pthread_mutex_lock(philo.next_fork_mutex);
	}
	else
	{
		pthread_mutex_lock(philo.next_fork_mutex);
		pthread_mutex_lock(&philo.fork_mutex);
	}
	*philo.fork = 0;
	*philo.next_fork = 0;
	pthread_mutex_unlock(&philo.fork_mutex);
	pthread_mutex_unlock(philo.next_fork_mutex);
}

void	eat(t_philo philo)
{

}
