/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:40:03 by schiper           #+#    #+#             */
/*   Updated: 2025/06/02 18:53:37 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	t_philo	threads[MAX_THREADS];
	t_mutex	forks[MAX_THREADS];
	t_data	engine;

	if ((validate(argc, argv)) == 1)
		return (1);
	engine.forks = forks;
	engine.philos = threads;
	init_data(&engine, argv);
	launcher(&engine, engine.count);
	return (0);
}
