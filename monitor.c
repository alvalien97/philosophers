/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:16:11 by hzsurf            #+#    #+#             */
/*   Updated: 2025/07/09 10:21:39 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_data *data)
{
	int		i;
	long	now;
	long	last_meal;

	now = get_time();
	i = 0;
	while (i < data->count)
	{
		pthread_mutex_lock(&data->meal_check);
		last_meal = data->philos[i].last_meal;
		pthread_mutex_unlock(&data->meal_check);
		if ((now - last_meal) > data->die)
		{
			pthread_mutex_lock(&data->print);
			if (!get_stop(data))
				printf("%ld %d died\n", now - data->start, i + 1);
			set_stop(data, 1);
			pthread_mutex_unlock(&data->print);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!get_stop(data))
	{
		if (check_death(data))
			break ;
		pthread_mutex_lock(&data->meal_check);
		if (data->max_meals != -1 && data->full_count == data->count)
		{
			data->stop = 1;
			pthread_mutex_unlock(&data->meal_check);
			break ;
		}
		pthread_mutex_unlock(&data->meal_check);
		usleep(1000);
	}
	return (NULL);
}
