/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:44:30 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/11 17:29:40 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "parsing.h"

static int	check_is_num(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[++i])
	{
		j = 0;
		if (str[i][j] == '+')
			j++;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (1);
			j++;
		}
		if (j == 0)
			return (1);
	}
	return (0);
}

static int	fill_data(int ac, char **av, t_data *data)
{
	data->num_of_philo = ft_atoi(av[1]);
	if (data->num_of_philo == -1)
		return (1);
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die == -1)
		return (1);
	data->time_to_eat = ft_atoi(av[3]);
	if (data->time_to_eat == -1)
		return (1);
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep == -1)
		return (1);
	if (ac == 6)
	{
		data->num_of_eat = ft_atoi(av[5]);
		if (data->num_of_eat == -1)
			return (1);
	}
	else
		data->num_of_eat = -1;
	return (0);
}

int	parsing(int ac, char **av, t_data *data)
{
	if (ac != 5 && ac != 6)
	{
		ft_putendl("put 4 or 5 args", 2);
		return (1);
	}
	if (check_is_num(av))
	{
		ft_putendl("only posisitve num are able", 2);
		return (1);
	}
	if (fill_data(ac, av, data))
	{
		ft_putendl("number too big", 2);
		return (1);
	}
	if (data->num_of_philo == 0)
	{
		ft_putendl("need at least 1 philo", 2);
		return (1);
	}
	return (0);
}
