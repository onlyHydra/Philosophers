/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:40:03 by schiper           #+#    #+#             */
/*   Updated: 2025/04/04 16:43:48 by schiper          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_philo			threads[MAX_THREADS];
	pthread_mutex_t	dead_mutex;
	static int		dead_flag;

	dead_flag = 0;
	check_args(argc, argv);
	return (execute(init_data(argc, argv)));
}
