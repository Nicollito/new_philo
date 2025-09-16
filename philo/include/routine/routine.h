/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:06:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/15 21:18:24 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"

#  define FORK "has taken a fork"
#  define EAT "is eating"
#  define SLEEP "is sleeping"
#  define THINK "is thinking"
#  define DIE "died"

typedef enum action
{
	TAKE,
	DEPOSIT,
}	t_action;

// actions.c

int		ft_sleep(t_philo *philo, t_data data);

void	think(t_philo *philo);

int		eat(t_philo *philo, t_data data);

// mutex.c

void	print_log(int timestamp, int philo, char *msg, pthread_mutex_t *mutex);

// routine.c

int		isdead(t_philo *philo, pthread_mutex_t *death_mutex);

int		ft_msleep(unsigned int ms, t_philo *philo);

#endif