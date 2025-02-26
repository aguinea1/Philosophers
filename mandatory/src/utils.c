/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:54:52 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/24 11:07:53 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;
	static time_t	start_time;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	}
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001) - start_time);
}

long	elapsed_time(t_philo *philo)
{
	return (get_time_ms() - philo->table->sim_start);
}

bool	is_it_dead(t_philo *philo)
{
	long	elapsed;

	pthread_mutex_lock(&philo->meal_flag);
	elapsed = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_flag);
	if (elapsed > philo->table->tt_die)
	{
		pthread_mutex_lock(&philo->table->table_mtx);
		philo->table->philo_dead = true;
		pthread_mutex_unlock(&philo->table->table_mtx);
		return (true);
	}
	return (false);
}

void	do_usleep(long ms)
{
	long	init;

	init = get_time_ms();
	while (get_time_ms() - init < ms)
		usleep(100);
}
