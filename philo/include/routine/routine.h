/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:06:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/10 11:47:59 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"

#  define FORK "has taken a fork"
#  define EAT "is eating"
#  define SLEEP "is sleeping"
#  define THINK "is thinking"

typedef enum action
{
	TAKE,
	DEPOSIT,
}	t_action;

// actions.c

void	sleep(t_philo *philo);

void	think(t_philo *philo);

void	eat(t_philo *philo);

// mutex.c

void	print_log(int timestamp, int philo, char *msg);

#endif