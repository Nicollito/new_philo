/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_threads.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:53:13 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/17 17:14:13 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_THREADS_H
# define MY_THREADS_H

# include "philo.h"

/* -------------routine------------- */

// routine.c

void	*routine(void *philo);

/* -------------threads------------- */

// state_of_philo.c

void	set_state_philo(t_philo *philo, t_state current);

t_state	check_state(t_philo *current, t_data *data,
			t_philo *philo, int timestamp);

void	look_for_die(t_data *data, t_philo *philo);

#endif