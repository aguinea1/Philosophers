/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:08:41 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/27 15:11:32 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

static int	check_meal_count(t_philo *philo, int *flag_meals, t_table *table)
{
	if (philo->n_meal == table->num_eat)
		(*flag_meals)++;
	 if (table->num_philo == *flag_meals)
		return (1);
	return (0);
}

static int	check_death(t_philo *philo, t_table *table)
{
	if (is_it_dead(philo))
	{
		sem_wait(table->print_sem);
		printf(RED "%-6ld %d died\n" RESET, get_time_ms(), philo->id);
		sem_post(table->print_sem);
		return (1);
	}
	return (0);
}

void	*monitor(void	*data)
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

