/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:08:41 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/14 19:40:05 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

static void	monitor_meal(t_philo *philo)
{
	int	i;

	i = 0;
	while (philo[i].id < philo->table->num_philo
		&& philo->table->num_eat != -1)
	{
		if (philo[i].n_meal < philo->table->max_meals)
			break ;
		if (philo[i].id + 1 == philo->table->num_philo)
		{
			sem_post(philo->table->finish);
			return ;
		}
		i++;
	}
}

void	*monitor(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (1)
	{
		sem_wait(philo->table->death_sem);
		if (philo->next_meal < get_time_ms())
		{
			sem_wait(philo->table->print_sem);
			printf(RED "%-6ld %d %s\n" RESET, get_time_ms(), philo->id, "died");
			return (sem_post(philo->table->finish), NULL);
		}
		sem_post(philo->table->death_sem);
		sem_wait(philo->table->death_sem);
		sem_wait(philo->table->print_sem);
		if (philo->table->num_philo % 2 == 0)
			monitor_meal(philo);
		sem_post(philo->table->print_sem);
		sem_post(philo->table->death_sem);
	}
	return (NULL);
}
