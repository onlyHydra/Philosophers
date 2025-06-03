/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:40:03 by schiper           #+#    #+#             */
/*   Updated: 2025/06/03 13:45:27 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_data *engine)
{
	int	count;

	count = engine->count;
	while (--count >= 0)
		pthread_mutex_destroy(&engine->forks[count]);
	pthread_mutex_destroy(&engine->write_lock);
	pthread_mutex_destroy(&engine->food_lock);
	pthread_mutex_destroy(&engine->dead_lock);
	free(engine->forks);
	engine->forks = NULL;
	free(engine->philos);
	engine->philos = NULL;
	free(engine);
}

void	debug_print(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->write_lock);
	printf("%s %d StopFlage:%d \n", message, philo->id, *philo->stop);
	pthread_mutex_unlock(philo->write_lock);
}

int	validate(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		write(1, "Wrong argument", ft_strlen("Wrong argument"));
		return (1);
	}
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 11 || ft_atoi(argv[i]) > INT_MAX
			|| ft_atoi(argv[i]) < 1)
		{
			write(1, "Arg wrong type", ft_strlen("Arg wrong type"));
			return (1);
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > MAX_THREADS)
	{
		write(1, "Incorect philo", ft_strlen("Incorect philo"));
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*threads;
	t_mutex	*forks;
	t_data	*engine;

	if ((validate(argc, argv)) == 1)
		return (1);
	threads = malloc(sizeof(t_philo) * MAX_THREADS);
	forks = malloc(sizeof(t_mutex) * MAX_THREADS);
	engine = malloc(sizeof(t_data));
	engine->forks = forks;
	engine->philos = threads;
	if (init_data(engine, argv) == my_true)
		launcher(engine, engine->count);
	else
	{
		free(engine->forks);
		free(engine->philos);
		free(engine);
	}
	return (0);
}
