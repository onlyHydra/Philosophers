/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:40:03 by schiper           #+#    #+#             */
/*   Updated: 2025/04/03 18:41:09 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_validator.h"
#include "philosophers.h"

int	execute(void)
{
	pthread_mutex_lock(dead_flag);
	if (dead_flag == 0)
		pick_fork();
	pthread_mutex_unlock(dead_flag);
	pthread_mutex_lock(dead_flag);
	if (dead_flag == 0)
		eat_meals();
	pthread_mutex_unlock(dead_flag);
	pthread_mutex_lock(dead_flag);
	if (dead_flag == 0)
		tp_sleep();
	pthread_mutex_unlock(dead_flag);
	pthread_mutex_lock(dead_flag);
	if (dead_flag == 0)
		wake();
	pthread_mutex_unlock(dead_flag);
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
