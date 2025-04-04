/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:16:14 by schiper           #+#    #+#             */
/*   Updated: 2025/04/04 16:45:55 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PHILOSOPHERS_H)
# define PHILOSOPHERS_H

# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define MAX_THREADS 61736

typedef pthread_mutex_t	t_mutex;

typedef enum e_states
{
	ALIVE,
	DEAD,
}						t_states;

typedef struct s_params
{
	int					id;
	int					meal_num;
	t_states			state;
	pthread_mutex_t		*forks;

}						t_params;

typedef struct s_locks
{
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	t_mutex				*write_lock;
	t_mutex				*meal_lock;
}						t_locks;

typedef struct s_timestamp
{
	size_t				die;
	size_t				eat;
	size_t				sleep;
	size_t				last_meal;
	size_t				born_time;
}						t_tstamp;

typedef struct s_philo
{
	int					id;
	t_tstamp			time_track;
	t_locks				locks;
	int					nb_of_meals;
	pthread_t			thread_id;
	int					forks;
	int					must_eat;
	t_states			state;
}						t_philo;

typedef struct s_data
{
	t_mutex				*forks;
	t_philo				*philos;
	t_mutex				food_lock;
	t_mutex				write_lock;

}						t_data;

long					ft_atoi(const char *nptr);
void					check_death(t_philo *philo);
t_bool					check_done_eating(t_philo *philos, int philo_count);
void					eat(t_philo *philo);
void					pick_up_forks(t_philo *philo);
#endif // PHILOSOPHERS_H
