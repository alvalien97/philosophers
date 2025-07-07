/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:16:25 by hzsurf            #+#    #+#             */
/*   Updated: 2025/07/07 20:20:16 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *ph)
{
	if (ph->id % 2 == 0)
		pthread_mutex_lock(ph->right);
	else
		pthread_mutex_lock(ph->left);
	if (ph->id % 2 == 0)
		pthread_mutex_lock(ph->left);
	else
		pthread_mutex_lock(ph->right);
	pthread_mutex_lock(&ph->data->meal_check);
	print_action(ph, "is eating");
	ph->last_meal = get_time();
	ph->meals++;
	pthread_mutex_unlock(&ph->data->meal_check);
	ft_usleep(ph->data->eat);
	pthread_mutex_unlock(ph->left);
	pthread_mutex_unlock(ph->right);
}

void	*philo_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		usleep(1000);
	while (!ph->data->stop)
	{
		philo_eat(ph);
		pthread_mutex_lock(&ph->data->meal_check);
		if (ph->data->max_meals != -1 && ph->meals == ph->data->max_meals)
		{
			ph->data->full_count++;
			pthread_mutex_unlock(&ph->data->meal_check);
			break ;
		}
		pthread_mutex_unlock(&ph->data->meal_check);
		print_action(ph, "is sleeping");
		ft_usleep(ph->data->sleep);
		print_action(ph, "is thinking");
	}
	return (NULL);
}
