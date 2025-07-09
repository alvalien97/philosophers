/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:15:44 by hzsurf            #+#    #+#             */
/*   Updated: 2025/07/09 10:18:47 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->count)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print, NULL))
		return (0);
	if (pthread_mutex_init(&data->meal_check, NULL))
		return (0);
	if (pthread_mutex_init(&data->stop_lock, NULL))
		return (0);
	return (1);
}

void	init_philos(t_data *d)
{
	int	i;

	d->start = get_time();
	i = 0;
	while (i < d->count)
	{
		d->philos[i].id = i;
		d->philos[i].meals = 0;
		d->philos[i].last_meal = d->start;
		d->philos[i].left = &d->forks[i];
		d->philos[i].right = &d->forks[(i + 1) % d->count];
		d->philos[i].data = d;
		i++;
	}
}

int	init_all(t_data *d, int ac, char **av)
{
	d->count = atoi(av[1]);
	if (d->count == 1)
	{
		write(2, "0 1 died\n", 9);
		return (0);
	}
	d->die = atoi(av[2]);
	d->eat = atoi(av[3]);
	d->sleep = atoi(av[4]);
	if (ac == 6)
		d->max_meals = atoi(av[5]);
	else
		d->max_meals = -1;
	d->stop = 0;
	d->forks = malloc(sizeof(pthread_mutex_t) * d->count);
	d->philos = malloc(sizeof(t_philo) * d->count);
	if (!d->forks || !d->philos || !init_mutexes(d))
		return (0);
	init_philos(d);
	return (1);
}
