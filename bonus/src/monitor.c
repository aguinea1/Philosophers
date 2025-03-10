/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:08:41 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 00:56:46 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"
/*
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
	if (table->philo_dead == true)
	{
		return (print_status(philo, DIE), 1);
	}
	return (0);
}
*/
void	*monitor(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->table->death_sem);
		if (philo->next_meal < get_time_ms())
		{	
			printf(RED "%-6ld %d %s\n" RESET, get_time_ms(), philo->id, "died");
			sem_post(philo->table->finish);
			return (NULL);
		}
		sem_post(philo->table->death_sem);
		sem_wait(philo->table->death_sem);
		if ((philo->table->num_eat != -1) && (philo->table->n_meal * philo->table->num_philo >= philo->table->max_meals))
		{
			sem_post(philo->table->finish);
			return (NULL);
		}
			sem_post(philo->table->death_sem);
	}
	return (NULL);
}

