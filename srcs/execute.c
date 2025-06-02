/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:03:54 by schiper           #+#    #+#             */
/*   Updated: 2025/06/02 18:38:10 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_bool.h"
#include "philosophers.h"

size_t	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		printf("gettimeofday() error\n");
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

static void	think(t_philo *philo)
{
	print_action(philo, " is thinking");
}

static void	dinning(t_philo *philo)
{
	pthread_mutex_lock(philo->locks.right_fork);
	print_action(philo, "picked right fork");
	if (philo->nb_of_philos == 1)
	{
		ft_usleep(philo->die);
		pthread_mutex_unlock(philo->locks.right_fork);
		return ;
	}
	pthread_mutex_lock(philo->locks.left_fork);
	print_action(philo, "picked left fork");
	philo->eatting = my_true;
	print_action(philo, "is eatting");
	pthread_mutex_lock(philo->locks.meal_lock);
	philo->last_meal = get_current_time();
	philo->nb_of_meals++;
	pthread_mutex_unlock(philo->locks.meal_lock);
	ft_usleep(philo->eat);
	philo->eatting = my_false;
	pthread_mutex_unlock(philo->locks.left_fork);
	pthread_mutex_unlock(philo->locks.right_fork);
	print_action(philo, "is sleeping");
	ft_usleep(philo->sleep);
}

void	*start_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!stop_check_loop(philo))
	{
		dinning(philo);
		think(philo);
	}
	return (arg);
}

void	launcher(t_data *engine, int count)
{
	int	i;

	i = -1;
	if (pthread_create(&engine->monitor, NULL, observer, engine->philos) != 0)
		destroy_all(engine, "[Observer Creation ERROR]\n", count, 1);
	while (++i < count)
	{
		if (pthread_create(&engine->philos[i].thread, NULL, start_simulation,
				&engine->philos[i]) != 0)
			destroy_all(engine, "[Thread Creation ERROR]\n", count, 1);
	}
	if (pthread_join(engine->monitor, NULL) != 0)
		destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
	i = -1;
	while (++i < count)
	{
		if (pthread_join(engine->philos[i].thread, NULL) != 0)
			destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
	}
}
