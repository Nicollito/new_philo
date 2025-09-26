/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timestamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:11:10 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/26 13:03:59 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

int	get_timestamp(void)
{
	int						res;
	static int				first = 1;
	struct timeval			now;
	static struct timeval	start;

	if (first)
	{
		first = 0;
		gettimeofday(&start, NULL);
	}
	gettimeofday(&now, NULL);
	res = ((now.tv_sec * 1000) + (now.tv_usec / 1000))
		- ((start.tv_sec * 1000) + (start.tv_usec / 1000));
	return (res);
}

/* int is_time_to_start(t_philo philo)
{
	
} */
