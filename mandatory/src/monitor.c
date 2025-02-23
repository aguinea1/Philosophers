/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 15:13:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/21 01:16:22 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	*monitor(void *data)
{
	t_table *table;
	int i;
	int	flag_meals = 0;

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
			pthread_mutex_lock(&table->table_mtx);
			if (is_it_dead(&table->philo[i]))
			{
				pthread_mutex_unlock(&table->table_mtx);
				 pthread_mutex_lock(&table->print_mtx);
				 printf(RED "%-6ld %d died\n" RESET,  get_time_ms(), table->philo->id);
				 pthread_mutex_unlock(&table->print_mtx);
				 destroy_mutex(table);
				 free(table->philo);
				 exit(1); 
			}
			pthread_mutex_unlock(&table->table_mtx);
			if (flag_meals == table->num_philo)
			{
				pthread_mutex_lock(&table->table_mtx);
				table->all_meals = true;
				pthread_mutex_unlock(&table->table_mtx);
				return (NULL);
			}
			 i++;
		}
		usleep(1000);
	}
	return NULL;
}


