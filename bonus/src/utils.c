/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:46:49 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/27 16:54:53 by aguinea          ###   ########.fr       */
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
	long	elapsed;

	sem_wait(philo->table->table_sem);
	elapsed = get_time_ms() - philo->last_meal;
	sem_post(philo->table->table_sem);
	if (elapsed > philo->table->tt_die)
	{
		printf("elapsed = %ld\n lm = %ld\n , id = %i\n", elapsed, philo->last_meal, philo->id);
		sem_wait(philo->table->death_sem);
		philo->table->philo_dead = true;
		sem_post(philo->table->death_sem);
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
