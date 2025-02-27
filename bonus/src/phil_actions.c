/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:39:18 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/27 16:37:31 by aguinea          ###   ########.fr       */
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
	sem_wait(philo->table->forks_sem);
	print_status(philo, FORK);
	sem_wait(philo->table->table_sem);
	philo->last_meal = elapsed_time(philo);
	printf("philo lm = %ld, philo id = %i\n", philo->last_meal, philo->id);
	philo->n_meal++;
	sem_post(philo->table->table_sem);
	print_status(philo, EAT);
	usleep(philo->table->tt_eat * 1000);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
}
/*
void	eat(t_philo *philo)
{
	fork_act(philo);
	sem_wait(philo->table->table_sem);
	philo->last_meal = elapsed_time(philo);
	philo->n_meal++;
	sem_post(philo->table->table_sem);
	print_status(philo, EAT);
	usleep(philo->table->tt_eat * 1000);
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
}
*/
void	sleep_act(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->table->tt_sleep * 1000);
}
/*
void	fork_act(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		sem_wait(philo->table->forks_sem);
		print_status(philo, FORK);
		sem_wait(philo->table->forks_sem);
		print_status(philo, FORK);
	}
	else
	{
		usleep(1000);
		sem_wait(philo->table->forks_sem);
		print_status(philo, FORK);
		sem_wait(philo->table->forks_sem);
		print_status(philo, FORK);
	}
}*/

void	eat_lonely(t_philo *philo)
{
	if (philo->table->num_philo != 1)
		eat(philo);
	else
	{
		sem_wait(philo->table->forks_sem);
		print_status(philo, FORK);
		sem_wait(philo->table->table_sem);
		philo->last_meal = elapsed_time(philo);
		philo->n_meal++;
		sem_post(philo->table->table_sem);
		print_status(philo, EAT);
		usleep(philo->table->tt_eat * 1000);
		sem_post(philo->table->forks_sem);
	}
}
