/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:06:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/18 16:16:07 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef enum action
{
	TAKE,
	DEPOSIT,
}	t_action;

typedef enum call
{
	INIT,
	REUSED,
}	t_call;

// actions.c

t_state	ft_usleep(unsigned int us, t_philo *philo);

t_state	ft_sleep(t_philo *philo, t_data data);

void	think(t_philo *philo);

t_state	eat(t_philo *philo, t_data data, t_call call);

// mutex.c

void	print_log(int timestamp, int philo, char *msg, pthread_mutex_t *mutex);

// routine.c

t_state	isdead(t_philo *philo, pthread_mutex_t *death_mutex);

#endif