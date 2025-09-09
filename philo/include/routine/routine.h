/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 14:06:29 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/09 15:34:21 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROUTINE_H
# define ROUTINE_H

# include "philo.h"

#  define FORK "has taken a fork"
#  define EAT "is eating"
#  define SLEEP "is sleeping"
#  define THINK "is thinking"

// actions.c

void	think(t_philo philo);

// mutex.c

void	print_log(int timestamp, int philo, char *msg);

#endif