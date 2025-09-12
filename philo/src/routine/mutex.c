/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:59:52 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/12 14:09:39 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_log(int timestamp, int philo, char *msg, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%d %d %s\n", timestamp, philo, msg);
	pthread_mutex_unlock(mutex);
}
