/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:39:45 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/26 16:49:23 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

typedef enum state
{
	ALIVE,
	DEAD,
	FED,
	WAIT,
	READY,
}	t_state;

typedef struct start
{
	int				ready_count;
	t_state			start;
	pthread_mutex_t	ready_mutex;
	pthread_mutex_t	start_mutex;
}					t_start;

typedef struct data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eat;
	t_start			*start;
}					t_data;

typedef struct philo
{
	int				num;
	t_state			state;
	int				last_meal;
	int				nbr_of_eat;
	int				*fork;
	int				*next_fork;
	struct data		*data;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*next_fork_mutex;
	pthread_mutex_t	*printf_mutex;
	pthread_t		threads;
}					t_philo;

/* ----------------init----------------- */

// all_free.c

void	free_philo(t_philo *philo);

// init.c

t_philo	*init_philo(t_data *data);

/* ---------------parsing--------------- */

// parsing.c

int		parsing(int ac, char **av, t_data *data, t_start *start);

/* ---------------routine---------------- */

// timestamp.c

int		get_timestamp(void);

/* ----------------threads---------------- */

// manage_threads.c

int		manage_threads(t_data *data, t_philo *philo);

#endif