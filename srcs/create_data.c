/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:09:10 by schiper           #+#    #+#             */
/*   Updated: 2025/04/09 15:16:36 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_data	*allocate_data_memory(int count)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
	{
		write(1, "Memory allocation error for data\n", 32);
		return (NULL);
	}
	data->philos = (t_philo *)malloc(sizeof(t_philo) * count);
	if (!data->philos)
	{
		write(1, "Memory allocation error for philosophers\n", 41);
		free(data);
		return (NULL);
	}
	data->forks = (t_mutex *)malloc(sizeof(t_mutex) * count);
	if (!data->forks)
	{
		write(1, "Memory allocation error for forks\n", 35);
		free(data->philos);
		free(data);
		return (NULL);
	}
	return (data);
}

int	initialize_mutexes(t_data *data, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			write(1, "Mutex initialization error for forks\n", 38);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->food_lock, NULL) != 0)
	{
		write(1, "Mutex initialization error for food lock\n", 41);
		return (0);
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		write(1, "Mutex initialization error for write lock\n", 43);
		return (0);
	}
	return (1);
}

int	initialize_philosophers(t_data *data, int count, char **argv)
{
	int	i;

	i = 0;
	while (i < count)
	{
		data->philos[i].id = i;
		data->philos[i].nb_of_meals = 0;
		data->philos[i].must_eat = ft_atoi(argv[1]);
		data->philos[i].state = ALIVE;
		data->philos[i].forks = 0;
		data->philos[i].engine = data;
		if (pthread_mutex_init(&data->philos[i].locks.meal_lock, NULL) != 0)
		{
			write(1, "Mutex initialization error for meal lock\n", 41);
			return (0);
		}
		i++;
	}
	return (1);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;
	int		philo_count;

	philo_count = ft_atoi(argv[0]);
	data = allocate_data_memory(philo_count);
	if (!data)
		return (NULL);
	if (!initialize_mutexes(data, philo_count))
	{
		destroy_all(data, "Mutex initialization failed.\n", philo_count, 1);
		return (NULL);
	}
	if (!initialize_philosophers(data, philo_count, argv))
	{
		destroy_all(data, "Philosopher initialization failed.\n", philo_count,
			1);
		return (NULL);
	}
	data->count = philo_count;
	return (data);
}
