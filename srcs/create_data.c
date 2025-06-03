/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:09:10 by schiper           #+#    #+#             */
/*   Updated: 2025/06/03 13:39:12 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	initialize_mutexes(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(1, "Mutex initialization error for forks\n", 38);
			return (my_false);
		}
		i++;
	}
	if (pthread_mutex_init(&(data->food_lock), NULL) != 0)
		return (my_false);
	if (pthread_mutex_init(&(data->write_lock), NULL) != 0)
		return (my_false);
	if (pthread_mutex_init(&(data->dead_lock), NULL) != 0)
		return (my_false);
	return (my_true);
}

static void	ft_data_init(t_philo *philo, char **argv)
{
	philo->nb_of_philos = ft_atol(argv[1]);
	philo->die = ft_atol(argv[2]);
	philo->eat = ft_atol(argv[3]);
	philo->sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		philo->must_eat = ft_atol(argv[5]);
	else
		philo->must_eat = -1;
}

static t_bool	initialize_philosophers(t_data *data, int count, char **argv)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		data->philos[i].id = i + 1;
		data->philos[i].nb_of_meals = 0;
		data->philos[i].eatting = my_false;
		data->philos[i].must_eat = ft_atoi(argv[1]);
		data->philos[i].born_time = get_current_time();
		data->philos[i].last_meal = get_current_time();
		data->philos[i].stop = &data->done;
		data->philos[i].left_fork = &(data->forks[i]);
		data->philos[i].write_lock = &(data->write_lock);
		data->philos[i].dead = &(data->dead_lock);
		data->philos[i].meal_lock = &(data->food_lock);
		data->philos[i].die = my_false;
		data->philos[i].right_fork = &(data->forks[(i + 1) % count]);
		ft_data_init(&data->philos[i], argv);
	}
	return (my_true);
}

t_bool	init_data(t_data *data, char **argv)
{
	int	philo_count;

	philo_count = ft_atoi(argv[1]);
	data->done = my_false;
	if (!initialize_mutexes(data, philo_count))
	{
		destroy_all(data, "Mutex initialization failed.\n", philo_count, 1);
		return (my_false);
	}
	if (!initialize_philosophers(data, philo_count, argv))
	{
		destroy_all(data, "Philosopher initialization failed.\n", philo_count,
			1);
		return (my_false);
	}
	data->count = philo_count;
	return (my_true);
}
