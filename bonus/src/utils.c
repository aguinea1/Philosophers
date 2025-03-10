/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:46:49 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 10:48:48 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

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
	if (philo->next_meal < get_time_ms())
	{
		philo->table->philo_dead = true;
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
