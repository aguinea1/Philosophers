/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:45:48 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 10:31:03 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"
/*
static int	check_other(t_philo *philo)
{
	sem_wait(philo->table->death_sem);
	if (philo->n_meal != philo->table->num_eat && philo->table->philo_dead == false)
	{
		sem_post(philo->table->death_sem);
		return (1);
	}
	else
		sem_post(philo->table->death_sem);
	return (0);
}

static int	check_eat(t_philo *philo)
{
	sem_wait(philo->table->death_sem);
	if (philo->n_meal != philo->table->num_eat && philo->table->philo_dead == false)
	{
		sem_post(philo->table->death_sem);
		return (1);
	}
	else
		sem_post(philo->table->death_sem);
	return (0);
}
*/
void	*routine(t_philo *philo)
{
	pthread_t	monitor_t;
	
	philo->next_meal = (unsigned int)get_time_ms() + philo->table->tt_die;
	pthread_create(&monitor_t, NULL, monitor, philo);
	pthread_detach(monitor_t);
	/*if (!is_it_dead(philo) && philo->id % 2 != 0)
		usleep((philo->table->tt_eat - 1) * 1000);*/
	while (1)
	{
		if (is_it_dead(philo))
		{
			sem_wait(philo->table->print_sem);
			break;
		}
		//sem_post(philo->table->death_sem);
		//if (check_eat(philo))
		eat_lonely(philo);
		//else
		//	break ;
	//	if (check_other(philo))
	//	{
		sleep_act(philo);
		think(philo);
	}
	return (NULL);
}


