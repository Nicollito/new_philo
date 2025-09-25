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

void	deposit_fork(t_philo *philo);

t_state	left_handed_philo(t_philo *philo);

#endif