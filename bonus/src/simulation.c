/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:45:48 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/14 18:23:16 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

void	*routine(t_philo *philo)
{
	pthread_t	monitor_t;

	sem_wait(philo->table->start_sem);
	sem_wait(philo->table->death_sem);
	philo->next_meal = (unsigned int)get_time_ms() + philo->table->tt_die;
	sem_post(philo->table->death_sem);
	pthread_create(&monitor_t, NULL, monitor, philo);
	pthread_detach(monitor_t);
	if (!is_it_dead(philo) && philo->id % 2 != 0)
		usleep((philo->table->tt_eat / 2) * 1000);
	while (1)
	{
		eat_lonely(philo);
		if (philo->table->num_philo % 2 != 0 && philo->id % 2 != 0)
		{
				if (philo->n_meal == philo->table->max_meals)
				{
						usleep(philo->table->tt_eat);
						sem_post(philo->table->finish);
				}
		}
		sleep_act(philo);
		think(philo);
	}
	return (NULL);
}

