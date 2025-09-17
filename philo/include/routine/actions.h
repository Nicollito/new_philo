/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:45:11 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/17 17:13:33 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "routine.h"

// eat_utils.c

int		action_on_fork(int *fork, t_action action);

void	take_first_fork(int *fork, pthread_mutex_t *mutex, t_action action);

int		take_second_fork(int *fork, pthread_mutex_t *mutex, t_action action);

void	hunger_priority(t_philo *philo);

int		left_handed_philo(t_philo *philo, t_action action);

#endif