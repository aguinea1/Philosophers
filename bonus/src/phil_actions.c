/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:39:18 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/13 20:17:55 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

void	think(t_philo *philo)
{
	print_status(philo, THINK);
}

void	eat(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	print_status(philo, FORK);
	if (!(philo->next_meal * 0.5 > get_time_ms()))
		usleep(100);
	sem_wait(philo->table->forks_sem);
	print_status(philo, FORK);
	print_status(philo, EAT);
	sem_wait(philo->table->death_sem);
	philo->last_meal = get_time_ms();
	philo->next_meal = philo->last_meal + (unsigned int)philo->table->tt_die;
	philo->n_meal++;
	sem_post(philo->table->death_sem);
	usleep((philo->table->tt_eat) * 1000);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
}

void	sleep_act(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->table->tt_sleep * 1000);
}

void	eat_lonely(t_philo *philo)
{
	if (philo->table->num_philo != 1)
		eat(philo);
	else
	{
		sem_wait(philo->table->forks_sem);
		print_status(philo, FORK);
		sem_wait(philo->table->forks_sem);
	}
}
