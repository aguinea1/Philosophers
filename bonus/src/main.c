
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:44:35 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 17:14:02 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

int	init_sim(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid == 0)
		{
			routine(&table->philo[i]);
			exit(0);
		}
		i++;
	}
	table->sim_start = get_time_ms();
	for (i = 0; i < table->num_philo; i++)
        sem_post(table->start_sem);
	return (1);
}

bool	init_sems(t_table *table)
{
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("start");
	sem_unlink("forks");
	sem_unlink("finish");
	table->death_sem = sem_open("death", O_CREAT, 0600, 1);
	table->print_sem = sem_open("print", O_CREAT, 0600, 1);
	table->start_sem = sem_open("start", O_CREAT, 0644, 0);
	table->finish = sem_open("finish", O_CREAT, 0600, 1);
	table->forks_sem = sem_open("forks", O_CREAT, 0600,
			table->num_philo);
	if (table->death_sem == SEM_FAILED || table->print_sem == SEM_FAILED
		|| table->start_sem == SEM_FAILED || table->forks_sem == SEM_FAILED)
		return (false);
	return (true);
}

void	prep_sim(t_table *table)
{
	int	i;

	i = -1;
	table->philo = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philo)
		ft_error(MALLOC_ERR, NULL);
	while (table->num_philo > ++i)
	{
		table->philo[i].id = i + 1;
		table->philo[i].dead = false;
		table->philo[i].last_meal = 0;
		table->philo[i].pid = -1;
		table->philo[i].table = table;
		table->philo[i].n_meal = 0;
	}
	return ;
}

void	init_struct(t_table *table, char **av)
{
	table->num_philo = ft_atoi(av[1]);
	table->tt_die = ft_atoi(av[2]);
	table->tt_eat = ft_atoi(av[3]);
	table->tt_sleep = ft_atoi(av[4]);
	table->philo_dead = false;
	table->all_meals = false;
	table->num_eat = -1;
	table->full_philos = 0;
	table->meal = 0;
	table->start = 0;
	table->num_meal = 0;
	table->i = 0;
	if (av[5])
		table->num_eat = ft_atoi(av[5]);
	table->max_meals = table->num_eat;
}

int	main(int ac, char **av)
{
	t_table	table;

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
	init_sems(&table);
	sem_wait(table.finish);
	init_sim(&table);
	sem_wait(table.finish);
	ph_end_processes(&table);
	free(table.philo);
	return (0);
}
