/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 22:13:18 by alvalien          #+#    #+#             */
/*   Updated: 2025/07/09 10:38:40 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_check);
	pthread_mutex_destroy(&data->stop_lock);
}

void	cleanup(t_data *d)
{
	destroy_mutexes(d);
	if (d->forks)
	{
		free(d->forks);
	}
	if (d->philos)
	{
		free(d->philos);
	}
}
