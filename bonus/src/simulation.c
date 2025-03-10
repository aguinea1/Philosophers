/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:45:48 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 10:57:04 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

void	*routine(t_philo *philo)
{
	pthread_t	monitor_t;

	philo->next_meal = (unsigned int)get_time_ms() + philo->table->tt_die;
	pthread_create(&monitor_t, NULL, monitor, philo);
	pthread_detach(monitor_t);
	while (1)
	{
		if (is_it_dead(philo))
			break ;
		eat_lonely(philo);
		sleep_act(philo);
		think(philo);
	}
	return (NULL);
}
