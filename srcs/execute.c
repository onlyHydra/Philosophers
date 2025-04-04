/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:03:54 by schiper           #+#    #+#             */
/*   Updated: 2025/04/04 16:44:03 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_bool.h"
#include "philosophers.h"

t_bool	done_eating(t_philo *philos, int philo_count)
{
	int	finished;
	int	i;

	i = -1;
	finished = 0;
	while (++i < philo_count)
	{
		phtread_mutex_lock(philos->locks.meal_lock);
		if (philos[i].nb_of_meals >= philos[i].must_eat)
			finished++;
		phtread_mutex_unloc(philos->locks.meal_lock);
	}
	return (finished == philo_count);
}

void	*start_simulation(void *ptr)
{
	t_philo	*philo;
	t_philo	*philos;
	int		philo_count;

	philo = (t_philo *)ptr;
	philos = philo->engine->philos;
	philo_count = philo->engine->count;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	pthread_mutex_lock(philo->locks.meal_lock);
	philo->time_track.born_time = get_current_time();
	philo->time_track.last_meal = get_current_time();
	pthread_mutex_unlock(philo->locks.meal_lock);
	while (!get_dead())
		philo_routine(philo, philos, philo_count);
	return (NULL);
}

void	launcher(t_engine *engine, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (pthread_create(&engine->philos[i].thread_id, NULL, start_simulation,
				&engine->philos[i]) != 0)
			destroy_all(engine, "[Thread Creation ERROR]\n", count, 1);
	}
	i = -1;
	while (++i < count)
	{
		if (pthread_join(engine->philos[i].thread_id, NULL) != 0)
			destroy_all(engine, "[Thread Join ERROR]\n", count, 1);
	}
}

void	philo_routine(t_philo *philo, t_philo *philos, int philo_count)
{
	if (get_dead())
		return ;
	pick_up_forks(philo);
	eat(philo);
	sleep_philo(philo);
	think(philo);
	if (check_done_eating(philos, philo_count))
		return ;
	check_death(philo);
}
