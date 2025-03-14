/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:06:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/13 18:43:41 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	think(t_philo *philo)
{
	print_status(philo, THINK);
}

void	eat(t_philo *philo)
{
	if (!((philo->last_meal + philo->table->tt_eat) * 0.5 > get_time_ms()))
		usleep(100);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK);
		pthread_mutex_lock(&philo->r_fork);
		print_status(philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->r_fork);
		print_status(philo, FORK);
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK);
	}
	pthread_mutex_lock(&philo->meal_flag);
	philo->last_meal = elapsed_time(philo);
	philo->n_meal++;
	pthread_mutex_unlock(&philo->meal_flag);
	print_status(philo, EAT);
	usleep(philo->table->tt_eat * 1000);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

int	eat_lonely(t_philo *philo)
{
	if (philo->table->num_philo != 1)
		return (eat(philo), 1);
	else
	{
		pthread_mutex_lock(&philo->r_fork);
		print_status(philo, FORK);
		usleep(philo->table->tt_die * 650);
		pthread_mutex_lock(&philo->table->print_mtx);
		printf(RED "%d %d died\n" RESET, philo->table->tt_die + 1, philo->id);
		pthread_mutex_unlock(&philo->table->print_mtx);
		pthread_mutex_unlock(&philo->r_fork);
		return (0);
	}
}

void	sleep_act(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->table->tt_sleep * 1000);
}
