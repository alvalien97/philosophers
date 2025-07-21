/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalien <alvalien@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:16:34 by hzsurf            #+#    #+#             */
/*   Updated: 2025/07/09 10:38:27 by alvalien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	static struct timeval	start;
	struct timeval			tv;

	gettimeofday(&tv, NULL);
	if (!start.tv_sec && !start.tv_usec)
		start = tv;
	return (((tv.tv_sec - start.tv_sec) * 1000) + ((tv.tv_usec - start.tv_usec)
			/ 1000));
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(100);
}

void	print_action(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->data->print);
	if (!get_stop(ph->data))
		printf("%ld %d %s\n", get_time() - ph->data->start, ph->id + 1, str);
	pthread_mutex_unlock(&ph->data->print);
}

int	get_stop(t_data *data)
{
	int	val;

	pthread_mutex_lock(&data->stop_lock);
	val = data->stop;
	pthread_mutex_unlock(&data->stop_lock);
	return (val);
}

void	set_stop(t_data *data, int val)
{
	pthread_mutex_lock(&data->stop_lock);
	data->stop = val;
	pthread_mutex_unlock(&data->stop_lock);
}
