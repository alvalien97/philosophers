/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:15:56 by hzsurf            #+#    #+#             */
/*   Updated: 2025/07/11 17:58:10 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *n)
{
	int	i;
	int	sign;
	int	value;

	i = 0;
	sign = 1;
	value = 0;
	while (n[i] == 32 || (n[i] >= 9 && n[i] <= 13))
		i++;
	if (n[i] == '+' || n[i] == '-')
	{
		if (n[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (n[i] > 47 && n[i] < 58)
	{
		value = (value * 10) + ((int)n[i] - 48);
		i++;
	}
	return (value * sign);
}

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

int	check_args(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (atoi(av[i]) <= 0)
		{
			write(2, "Error in your arguments\n", 23);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data		data;
	pthread_t	checker;
	int			i;

	if (ac < 5 || ac > 6)
		return (0);
	if (!check_args(ac, av) || !init_all(&data, ac, av))
	{
		return (1);
	}
	i = 0;
	while (i < data.count)
	{
		pthread_create(&data.philos[i].thread, NULL, philo_routine,
			&data.philos[i]);
		i++;
	}
	pthread_create(&checker, NULL, monitor, &data);
	i = 0;
	while (i < data.count)
		pthread_join(data.philos[i++].thread, NULL);
	pthread_join(checker, NULL);
	cleanup(&data);
	return (0);
}
