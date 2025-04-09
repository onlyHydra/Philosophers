/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:40:03 by schiper           #+#    #+#             */
/*   Updated: 2025/04/09 15:11:01 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_validator.h"
#include "philosophers.h"

static t_bool	g_dead = my_false;

t_bool	get_dead(void)
{
	return (g_dead);
}

void	set_dead(t_bool my_bool)
{
	g_dead = my_bool;
}

static int	check_args(int argc, char **argv)
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
	if (ft_atoi(argv[0]) < 1 || ft_atoi(argv[0]) > MAX_THREADS)
	{
		write(1, "Incorect philo", ft_strlen("Incorect philo"));
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo			threads[MAX_THREADS];
	pthread_mutex_t	dead_mutex;
	static int		dead_flag;

	dead_flag = 0;
	if (check_args(argc, argv + 1) == 1)
		return (1);
	launch(init_data(argc, argv + 1));
	return (0);
}
