/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 11:33:00 by schiper           #+#    #+#             */
/*   Updated: 2025/06/05 18:38:02 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	attempt_eat(t_philo *philo)
{
	print_action(philo, "is eating", GREEN);
	philo->eatting = my_true;
	philo->last_meal = get_current_time();
	philo->nb_of_meals++;
}

static t_bool	pick_forks(t_philo *philo)
{
	if (stop_check_loop(philo))
		return (my_false);
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
	return (my_true);
}

t_bool	attempt_fork(t_philo *philo)
{
	if (stop_check_loop(philo))
		return (my_false);
	if (philo->nb_of_philos == 1)
	{
		ft_usleep(philo->die);
		print_action(philo, "picked right fork", GREEN);
		return (my_false);
	}
	if (pick_forks(philo) == my_false)
	{
		print_action(philo, "Failed fork", RED);
		return (my_false);
	}
	return (my_true);
}

void	release_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
