/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:08:08 by schiper           #+#    #+#             */
/*   Updated: 2025/04/09 15:04:35 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	think(t_philo *philo)
{
	print_action(philo, " is thinking");
}

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
	{
		i++;
	}
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
		{
			sign = sign * -1;
		}
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}
