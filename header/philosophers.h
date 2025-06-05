/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 15:16:14 by schiper           #+#    #+#             */
/*   Updated: 2025/06/05 18:32:00 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(PHILOSOPHERS_H)
# define PHILOSOPHERS_H

# include "my_bool.h"
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_THREADS 3000

# define RESET "\033[0m"
# define RED "\033[31m"
# define GREEN "\033[32m"

typedef pthread_mutex_t	t_mutex;

typedef struct s_params
{
	int					id;
	int					meal_num;
	pthread_mutex_t		*forks;

}						t_params;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					nb_of_meals;
	int					nb_of_philos;
	int					must_eat;
	t_bool				*stop;
	t_bool				eatting;
	size_t				die;
	size_t				eat;
	size_t				sleep;
	size_t				last_meal;
	size_t				born_time;
	t_mutex				*left_fork;
	t_mutex				*right_fork;
	t_mutex				*write_lock;
	t_mutex				*meal_lock;
	t_mutex				*dead;
}						t_philo;

typedef struct s_data
{
	pthread_t			monitor;
	t_mutex				*forks;
	t_philo				*philos;
	t_mutex				food_lock;
	t_mutex				write_lock;
	t_mutex				dead_lock;
	t_bool				done;

	int					count;

}						t_data;

int						ft_atoi(const char *nptr);

void					error_message(char *text, int signal);
void					destroy_all(t_data *engine, char *str, int count,
							int signal);
void					*observer(void *arg);
void					print_action(t_philo *philo, char *action, char *color);
size_t					get_current_time(void);
void					ft_usleep(size_t mls);
void					launcher(t_data *engine, int count);
t_bool					stop_check_loop(t_philo *philo);
t_bool					init_data(t_data *engine, char **argv);
int						ft_strlen(char *str);
size_t					get_time_ms(void);
long					ft_atol(char *s);
t_bool					attempt_fork(t_philo *philo);
void					release_forks(t_philo *philo);
void					debug_print(t_philo *philo, char *message);
void					free_all(t_data *engine);
void					attempt_eat(t_philo *philo);
#endif // PHILOSOPHERS_H
