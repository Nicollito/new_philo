/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:39:45 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/09 14:41:19 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef struct data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat;
	int	die;
}		t_data;

typedef struct philo
{
	int				num;
	int				last_eat;
	int				nbr_of_eat;
	int				*fork;
	int				*next_fork;
	struct data		*data;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	*next_fork_mutex;
	pthread_mutex_t	*printf_mutex;
	pthread_mutex_t	*death_mutex;
}					t_philo;

/* ----------------init----------------- */

// init.c

t_philo	*init_philo(t_data *data);

/* ---------------parsing--------------- */

// parsing.c

int		parsing(int ac, char **av, t_data *data);

/* ---------------routine---------------- */

int		get_timestamp();

#endif