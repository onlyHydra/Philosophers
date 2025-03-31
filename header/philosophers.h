/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:16:14 by schiper           #+#    #+#             */
/*   Updated: 2025/03/31 17:20:51 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PHILOSOPHERS_H)
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define MAX_THREADS 61736

typedef enum e_states
{
	EATING,
	THINKING,
	SLEEPING,
	DEAD,
}					t_states;

typedef struct s_params
{
	int				id;
	int				meal_num;
	t_states		state;
	pthread_mutex_t	*forks;

}					t_params;

typedef struct s_philo
{
}					t_philo;

#endif // PHILOSOPHERS_H
