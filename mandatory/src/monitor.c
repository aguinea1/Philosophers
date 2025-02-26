/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:13:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/24 14:56:18 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static int	check_meal_count(t_philo *philo, int *flag_meals, t_table *table)
{
	pthread_mutex_lock(&philo->meal_flag);
	if (philo->n_meal == table->num_eat)
		(*flag_meals)++;
	pthread_mutex_unlock(&philo->meal_flag);
	pthread_mutex_lock(&table->table_mtx);
	if (table->num_philo == *flag_meals)
		return (pthread_mutex_unlock(&table->table_mtx), 1);
	pthread_mutex_unlock(&table->table_mtx);
	return (0);
}

static int	check_death(t_philo *philo, t_table *table)
{
	if (is_it_dead(philo))
	{
		pthread_mutex_lock(&table->print_mtx);
		printf(RED "%-6ld %d died\n" RESET, get_time_ms(), philo->id);
		pthread_mutex_unlock(&table->print_mtx);
		return (1);
	}
	return (0);
}

void	*monitor(void *data)
{
	t_table	*table;
	int		i;
	int		flag_meals;

	table = (t_table *)data;
	while (1)
	{
		i = -1;
		flag_meals = 0;
		while (++i < table->num_philo)
		{
			if (check_meal_count(&table->philo[i], &flag_meals, table))
				return (NULL);
			if (check_death(&table->philo[i], table))
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
