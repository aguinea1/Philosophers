/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:54:52 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/20 16:14:09 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

long get_time_ms(void) 
{
    struct timeval tv;
	static time_t	start_time = 0;

	if (start_time == 0)
	{
		gettimeofday(&tv, NULL);
		start_time = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
	}
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001) - start_time);
}

long elapsed_time(t_philo *philo) 
{
    return (get_time_ms() - philo->table->sim_start);
}

bool	get_bool(t_mtx *data, bool *any, int flag)
{
	bool res;
	if (flag == 1)
	{
		pthread_mutex_lock(data);
		res = *any;
		pthread_mutex_unlock(data);
	}
	else if (flag == 2)
	{
		pthread_mutex_lock(data);
		res = true;
		pthread_mutex_unlock(data);
	}
	else if (flag == 3)
	{
		pthread_mutex_lock(data);
		res = false;
		pthread_mutex_unlock(data);
	}
	else
		res = false;  //Default case if flag is invalid
	return (res);
}

bool	is_it_dead(t_philo *philo)
{
	long	elapsed;

	pthread_mutex_lock(&philo->meal_flag);
	elapsed = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_flag);
/*	printf("%ld\n", elapsed);
	printf("%ld\n", philo->last_meal);
	printf("%i\n", philo->table->tt_die);*/
	if (elapsed > philo->table->tt_die)
	{
		philo->table->philo_dead = true;
		get_bool(&philo->meal_flag, &philo->dead, 2);
		return (1);
	}
	return (0);
}

void	do_usleep(long ms)
{
	long init;

	init = get_time_ms();
	while(get_time_ms() - init < ms)
		usleep(100);
}
