/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:08:41 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 10:54:59 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

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
			sem_post(philo->table->finish);
			return (NULL);
		}
		sem_post(philo->table->death_sem);
		sem_wait(philo->table->death_sem);
		if ((philo->table->num_eat != -1)
			&& (philo->table->n_meal * philo->table->num_philo
				>=philo->table->max_meals))
			return (sem_post(philo->table->finish), NULL);
		sem_post(philo->table->death_sem);
	}
	return (NULL);
}
