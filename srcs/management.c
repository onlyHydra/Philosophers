/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:48:19 by schiper           #+#    #+#             */
/*   Updated: 2025/04/09 15:13:48 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_message(char *text, int signal)
{
	if (text)
		write(2, text, ft_strlen(text) + 1);
	exit(signal);
}

void	destroy_all(t_data *engine, char *str, int count, int signal)
{
	while (--count >= 0)
		pthread_mutex_destroy(&engine->forks[count]);
	pthread_mutex_destroy(&engine->write_lock);
	pthread_mutex_destroy(&engine->food_lock);
	error_message(str, signal);
	free(engine->forks);
	free(engine->philos);
	free(engine);
}

void	print_action(t_philo *philo, char *action)
{
	size_t	time;

	pthread_mutex_lock(philo->locks.write_lock);
	time = get_current_time() - philo->time_track.born_time;
	printf(GREEN "[%ld]" RESET " %d%s\n", time, philo->id, action);
	pthread_mutex_unlock(philo->locks.write_lock);
}

size_t	get_current_time(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		error_message("[get time of day ERROR]\n", 1);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(size_t mls)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < mls)
		usleep(500);
}
