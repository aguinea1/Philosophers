/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:27:55 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/24 14:57:01 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

static void	init_sim(t_table *table)
{
	int	i;

	i = -1;
	if (table->num_eat == 0)
		return ;
	pthread_mutex_lock(&table->table_mtx);
	while (table->num_philo > ++i)
	{
		if (pthread_create(&table->philo[i].thread, NULL,
				&routine, &table->philo[i]))
		{
			ft_error(E_THREAD, NULL);
		}
	}
	pthread_mutex_unlock(&table->table_mtx);
	i = -1;
	while (++i < table->num_philo)
		pthread_join(table->philo[i].thread, NULL);
}

static int	prep_sim(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		ft_error(E_MALLOC, NULL);
	if (pthread_mutex_init(&table->table_mtx, NULL))
		ft_error(E_MTX, NULL);
	if (pthread_mutex_init(&table->print_mtx, NULL))
		ft_error(E_MTX, NULL);
	while (table->num_philo > ++i)
	{
		table->philo[i].id = i + 1;
		table->philo[i].dead = false;
		table->philo[i].last_meal = 0;
		table->philo[i].n_meal = 0;
		table->philo[i].table = table;
		if (pthread_mutex_init(&table->philo[i].r_fork, NULL))
			ft_error(E_MTX, NULL);
		if (table->philo[i].id != 1)
			table->philo[i].l_fork = &table->philo[i - 1].r_fork;
	}
	if (table->num_philo > 1)
		table->philo[0].l_fork = &table->philo[i - 1].r_fork;
	return (table->sim_start = get_time_ms(), 0);
}

static void	init_struct(t_table *table, char **av)
{
	table->num_philo = ft_atoi(av[1]);
	table->tt_die = ft_atoi(av[2]);
	table->tt_eat = ft_atoi(av[3]);
	table->tt_sleep = ft_atoi(av[4]);
	table->philo_dead = false;
	table->all_meals = false;
	table->num_eat = -1;
	table->full_philos = 0;
	if (av[5])
		table->num_eat = ft_atoi(av[5]);
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->print_mtx);
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->philo[i].meal_flag);
		pthread_mutex_destroy(&table->philo[i].r_fork);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_table		table;
	pthread_t	monitor_th;

	if (ac >= 5 && ac <= 6)
	{
		if (!parsing(ac, av))
			return (1);
	}
	else
	{
		printf ("%s", WRONG_ARGS);
		exit (EXIT_FAILURE);
	}
	init_struct(&table, av);
	prep_sim(&table);
	pthread_create(&monitor_th, NULL, monitor, &table);
	init_sim(&table);
	pthread_join(monitor_th, NULL);
	destroy_mutex(&table);
	free(table.philo);
	return (0);
}
