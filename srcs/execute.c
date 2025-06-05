/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:03:54 by schiper           #+#    #+#             */
/*   Updated: 2025/06/05 18:35:59 by schiper          ###   ########.fr       */
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
	pthread_mutex_lock(philo->dead);
	if (*philo->stop == my_false)
		print_action(philo, " is thinking", GREEN);
	pthread_mutex_unlock(philo->dead);
}

static int	dinning(t_philo *philo)
{
	if (stop_check_loop(philo))
		return (1);
	if (!attempt_fork(philo))
		return (1);
	pthread_mutex_lock(philo->meal_lock);
	if (stop_check_loop(philo))
	{
		pthread_mutex_unlock(philo->meal_lock);
		release_forks(philo);
		return (1);
	}
	attempt_eat(philo);
	pthread_mutex_unlock(philo->meal_lock);
	if (stop_check_loop(philo))
		return (release_forks(philo), 1);
	release_forks(philo);
	ft_usleep(philo->eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eatting = my_false;
	pthread_mutex_unlock(philo->meal_lock);
	if (stop_check_loop(philo))
		return (1);
	print_action(philo, "is sleeping", GREEN);
	ft_usleep(philo->sleep);
	return (0);
}

void	*start_simulation(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!stop_check_loop(philo))
	{
		if (!stop_check_loop(philo) && philo->nb_of_meals != philo->must_eat)
			dinning(philo);
		else
			break ;
		if (!stop_check_loop(philo) && philo->nb_of_meals != philo->must_eat)
			think(philo);
		else
			break ;
	}
	return (arg);
}

void	launcher(t_data *engine, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (pthread_create(&engine->philos[i].thread, NULL, start_simulation,
				&engine->philos[i]) != 0)
			destroy_all(engine, "[Thread Creation ERROR]\n", count, 1);
	}
	if (pthread_create(&engine->monitor, NULL, observer, engine->philos) != 0)
		destroy_all(engine, "[Observer Creation ERROR]\n", count, 1);
	if (pthread_join(engine->monitor, NULL) != 0)
		destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
	i = -1;
	while (++i < count)
	{
		if (pthread_join(engine->philos[i].thread, NULL) != 0)
			destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
	}
	free_all(engine);
}
