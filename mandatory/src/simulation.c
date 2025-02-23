/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 09:16:02 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/23 23:39:52 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static	void	think(t_philo *philo)
{
	print_status(philo, THINK);
}
static void	eat(t_philo *philo)
{
    if (philo->id % 2 == 0) // Even philosophers pick left first
    {
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, FORK);
        pthread_mutex_lock(&philo->r_fork);
        print_status(philo, FORK);
    }
    else // Odd philosophers pick right first
    {
        pthread_mutex_lock(&philo->r_fork);
        print_status(philo, FORK);
        pthread_mutex_lock(philo->l_fork);
        print_status(philo, FORK);
    }
    pthread_mutex_lock(&philo->meal_flag);
    philo->last_meal = elapsed_time(philo);
    philo->n_meal++;
    pthread_mutex_unlock(&philo->meal_flag);
    print_status(philo, EAT);
    usleep(philo->table->tt_eat * 1000);
	 // Unlock in reverse order
    pthread_mutex_unlock(&philo->r_fork);
    pthread_mutex_unlock(philo->l_fork);
}
/*
static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	print_status(philo, FORK);
	if (&philo->r_fork != philo->l_fork) // Prevent deadlock when alone
	{
		pthread_mutex_lock(philo->l_fork);
		print_status(philo, FORK);
		pthread_mutex_lock(&philo->meal_flag);
		philo->last_meal = elapsed_time(philo);
		philo->n_meal++;
		pthread_mutex_unlock(&philo->meal_flag);
		print_status(philo, EAT);
		usleep(philo->table->tt_eat * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(&philo->r_fork);
	}
	else
		usleep(philo->table->tt_die * 1000); // wait if only one fork
}*/

static void sleep_act(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->table->tt_sleep * 1000);
}

/*
void	*routine(void *data)
{
	t_philo *philo;

	philo = data;
	pthread_mutex_lock(&philo->table->table_mtx);
	pthread_mutex_unlock(&philo->table->table_mtx);
	if (!is_it_dead(philo) && philo->id % 2 != 0)
		usleep((philo->table->tt_eat - 1) * 1000);
	while(philo->n_meal != philo->table->num_eat && !is_it_dead(philo))
	{
		eat(philo);
		if (philo->n_meal != philo->table->num_eat)
		{
			sleep_act(philo);
			think(philo);
		}
	}
	return (NULL);
}
*/
void	*routine(void *data)
{
	t_philo *philo;
	
	philo = data;
	pthread_mutex_lock(&philo->table->table_mtx);
	pthread_mutex_unlock(&philo->table->table_mtx);
	if (!is_it_dead(philo) && philo->id % 2 != 0)
		usleep((philo->table->tt_eat - 1) * 1000);
	while(philo->n_meal != philo->table->num_eat && !is_it_dead(philo))
	{
		pthread_mutex_lock(&philo->table->table_mtx);
		if (!philo->table->philo_dead)
		{
			pthread_mutex_unlock(&philo->table->table_mtx);
			eat(philo);
		}
		else
		{
			pthread_mutex_unlock(&philo->table->table_mtx);
			break;
		}
		pthread_mutex_lock(&philo->table->table_mtx);
		if (philo->n_meal != philo->table->num_eat && !is_it_dead(philo))
		{
			pthread_mutex_unlock(&philo->table->table_mtx);
			sleep_act(philo);
			think(philo);
		}
		else
		{
			philo->table->full_philos++;
			pthread_mutex_unlock(&philo->table->table_mtx);
		}
	}
	return (NULL);
}
