/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:31:04 by schiper           #+#    #+#             */
/*   Updated: 2025/04/09 14:59:30 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_bool.h"
#include "philosophers.h"

void	pick_up_forks(t_philo *philo)
{
	if (get_dead())
		return ;
	pthread_mutex_lock(philo->locks.left_fork);
	print_action(philo, " has taken a fork");
	pthread_mutex_lock(philo->locks.right_fork);
	print_action(philo, " has taken a fork");
	check_death(philo);
}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->locks.meal_lock);
	print_action(philo, " is eating");
	philo->time_track.last_meal = get_current_time();
	philo->nb_of_meals += 1;
	pthread_mutex_unlock(philo->locks.meal_lock);
	ft_usleep(philo->time_track.eat);
	pthread_mutex_unlock(philo->locks.left_fork);
	pthread_mutex_unlock(philo->locks.right_fork);
}

void	sleep_philo(t_philo *philo)
{
	print_action(philo, " is sleeping");
	ft_usleep(philo->time_track.sleep);
}

t_bool	check_done_eating(t_philo *philos, int philo_count)
{
	if (done_eating(philos, philo_count))
	{
		pthread_mutex_lock(philos->locks.write_lock);
		print_action(philos, " All philosophers have eaten enough.");
		pthread_mutex_unlock(philos->locks.write_lock);
		return (my_true);
	}
	return (my_false);
}

void	check_death(t_philo *philo)
{
	pthread_mutex_lock(philo->locks.meal_lock);
	if (get_current_time()
		- philo->time_track.last_meal > philo->time_track.die)
	{
		pthread_mutex_unlock(philo->locks.meal_lock);
		print_action(philo, "died");
		pthread_mutex_lock(philo->locks.write_lock);
		set_dead(my_true);
		pthread_mutex_unlock(philo->locks.write_lock);
	}
	pthread_mutex_unlock(philo->locks.meal_lock);
}
