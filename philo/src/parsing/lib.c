/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nimadela <nimadela@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 14:03:57 by nimadela          #+#    #+#             */
/*   Updated: 2025/09/17 17:10:46 by nimadela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unistd.h"

static int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putendl(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	tmp;

	i = 0;
	res = 0;
	tmp = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		tmp = res * 10 + (str[i] - '0');
		if (tmp < res)
			return (-1);
		res = tmp;
		i++;
	}
	return (res);
}
