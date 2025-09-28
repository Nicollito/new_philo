/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:58:47 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/28 14:22:20 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "philo.h"

typedef struct mutex
{
	pthread_mutex_t	*fork;
	pthread_mutex_t	*printf;
}					t_mutex;

// set_malloc.c

int	malloc_table(int **fork, t_philo **philo, t_data *data);

int	malloc_mutex(t_mutex *mutex, t_data *data);

#endif