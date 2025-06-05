/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:12:33 by schiper           #+#    #+#             */
/*   Updated: 2025/06/05 18:37:56 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	philo_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time_ms() - philo->last_meal >= time_to_die && !philo->eatting)
		return (pthread_mutex_unlock(philo->meal_lock), my_true);
	pthread_mutex_unlock(philo->meal_lock);
	return (my_false);
}

static t_bool	is_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_of_philos)
	{
		if (philo_dead(&philos[i], philos[i].die))
		{
			print_action(&philos[i], "died", RED);
			pthread_mutex_lock(philos[0].dead);
			*philos->stop = my_true;
			pthread_mutex_unlock(philos[0].dead);
			return (my_true);
		}
		i++;
	}
	return (my_false);
}

static t_bool	is_enough_meals(t_philo *philos)
{
	int	i;
	int	all;

	i = 0;
	all = 0;
	if (philos[0].must_eat == -1)
		return (my_false);
	while (i < philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].nb_of_meals >= philos[i].must_eat)
			all++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (all == philos[0].nb_of_philos)
	{
		pthread_mutex_lock(philos[0].dead);
		*philos->stop = my_true;
		pthread_mutex_unlock(philos[0].dead);
		return (my_true);
	}
	return (my_false);
}

void	*observer(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (is_dead(philos) || is_enough_meals(philos))
			break ;
		ft_usleep(10);
	}
	return (arg);
}
