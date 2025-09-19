/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:45:11 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/18 15:46:53 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "routine.h"

// eat_utils.c

void	hunger_priority(t_philo *philo);

int		left_handed_philo(t_philo *philo, t_action action);

#endif