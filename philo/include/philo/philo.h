/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:39:45 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/08 16:42:41 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct data
{
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eat;
}		t_data;

typedef struct philo
{
	int	name;
	int	*fork;
	int	*next_fork;
}		t_philo;

// parsing.c

int	parsing(int ac, char **av, t_data *data);

#endif