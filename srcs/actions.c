/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:33:00 by schiper           #+#    #+#             */
/*   Updated: 2025/06/03 14:13:58 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	pick_forks(t_philo *philo)
{
	if (*philo->stop == my_false)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}
		else
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(philo->left_fork);
		}
		print_action(philo, "picked right fork", GREEN);
		print_action(philo, "picked left fork", GREEN);
	}
	else
		return (my_false);
	return (my_true);
}

t_bool	attempt_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	if (philo->nb_of_philos == 1)
	{
		ft_usleep(philo->die);
		print_action(philo, "picked right fork", GREEN);
		return (my_false);
	}
	if (pick_forks(philo) == my_false)
		return (my_false);
	pthread_mutex_unlock(philo->dead);
	return (my_true);
}
