/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:13:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/23 23:45:12 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*monitor(void *data)
{
	t_table *table;
	int i;
	int	flag_meals;

	table = (t_table *)data;
	while (1)
	{
		i = 0;
		flag_meals = 0;
		while(i < table->num_philo)
		{
			pthread_mutex_lock(&table->philo[i].meal_flag);
			if (table->philo[i].n_meal == table->num_eat)
				flag_meals++;
			pthread_mutex_unlock(&table->philo[i].meal_flag);
			if (is_it_dead(&table->philo[i]))
			{
				 pthread_mutex_lock(&table->print_mtx);
				 printf(RED "%-6ld %d died\n" RESET,  get_time_ms(), table->philo->id);
				 pthread_mutex_unlock(&table->print_mtx);
				 return NULL;
			}
			pthread_mutex_lock(&table->table_mtx);
			if (table->num_philo == flag_meals)
			{
				pthread_mutex_unlock(&table->table_mtx);
				return (NULL);
			}
			i++;
			pthread_mutex_unlock(&table->table_mtx);
		}
		usleep(1000);
	}
	return NULL;
}


