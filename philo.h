/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:16:55 by hzsurf            #+#    #+#             */
/*   Updated: 2025/07/09 10:38:09 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				count;
	int				die;
	int				eat;
	int				sleep;
	int				max_meals;
	int				stop;
	int				full_count;
	long			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check;
	pthread_mutex_t	stop_lock;
	t_philo			*philos;
}	t_data;

long	get_time(void);
void	ft_usleep(long time);
void	print_action(t_philo *ph, char *str);
int		init_all(t_data *data, int ac, char **av);
void	*philo_routine(void *arg);
int		check_death(t_data *data);
void	*monitor(void *arg);
void	cleanup(t_data *d);
void	destroy_mutexes(t_data *data);
int		get_stop(t_data *data);
void	set_stop(t_data *data, int val);

#endif
