/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:08:08 by schiper           #+#    #+#             */
/*   Updated: 2025/06/03 13:09:05 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	index;

	index = 0;
	if (str == NULL)
		return (0);
	while (str[index++])
		;
	return (index);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	number = 0;
	sign = 1;
	while ((nptr[i] == ' ') || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}

t_bool	stop_check_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (*philo->stop == my_true)
		return (pthread_mutex_unlock(philo->dead), my_true);
	pthread_mutex_unlock(philo->dead);
	return (my_false);
}

static t_bool	ft_isdigits(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!((s[i] >= '0' && s[i] <= '9') || s[i] == ' ' || s[i] == '\t'
				|| s[i] == '-' || s[i] == '+'))
			return (my_false);
		i++;
	}
	return (my_true);
}

long	ft_atol(char *s)
{
	int		i;
	long	nb;
	int		sign;

	if (!ft_isdigits(s))
		return (-42);
	i = 0;
	nb = 0;
	sign = 1;
	while (s[i] == ' ' || s[i] == '	')
		i++;
	if (s[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (s[i] == '+')
		i++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + (s[i] - '0');
		i++;
	}
	return (nb * sign);
}
