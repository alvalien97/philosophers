/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzsurf <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:16:34 by hzsurf            #+#    #+#             */
/*   Updated: 2025/07/07 20:16:36 by hzsurf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}

void	print_action(t_philo *ph, char *str)
{
	pthread_mutex_lock(&ph->data->print);
	if (!ph->data->stop)
		printf("%ld %d %s\n",
			get_time() - ph->data->start, ph->id + 1, str);
	pthread_mutex_unlock(&ph->data->print);
}
