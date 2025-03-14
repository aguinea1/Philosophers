/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:16:02 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 12:55:35 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static int	check_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_mtx);
	if (!philo->table->philo_dead)
	{
		pthread_mutex_unlock(&philo->table->table_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->table_mtx);
	return (0);
}

static int	check_other(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->table_mtx);
	if (philo->n_meal != philo->table->num_eat && !is_it_dead(philo))
	{
		pthread_mutex_unlock(&philo->table->table_mtx);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->table_mtx);
	return (0);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = data;
	pthread_mutex_lock(&philo->table->table_mtx);
	pthread_mutex_unlock(&philo->table->table_mtx);
	if (!is_it_dead(philo) && philo->id % 2 != 0)
		usleep((philo->table->tt_eat - 1) * 1000);
	while (philo->n_meal != philo->table->num_eat && !is_it_dead(philo))
	{
		if (check_eat(philo))
		{
			if (!eat_lonely(philo))
				return (NULL);
		}
		else
			break ;
		if (check_other(philo))
		{
			sleep_act(philo);
			think(philo);
		}
		else
			break ;
	}
	return (NULL);
}
