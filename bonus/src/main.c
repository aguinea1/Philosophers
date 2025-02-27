/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:44:35 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/27 15:39:12 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

void	init_sim(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	sem_unlink("start");
	sem_t *start_sem = sem_open("start", O_CREAT, 0600, 1);
	if (table->num_eat == 0)
		return ;
	table->sim_start = get_time_ms();
	while (table->num_philo > ++i)
	{
		table->philo[i].pid = fork();
		printf("After fork: Philosopher %d, pid: %d\n", i + 1, table->philo[i].pid);
		if (table->philo[i].pid < 0)
		{
			ft_error(FORK_ERR, NULL);
		}
		if (table->philo[i].pid == 0)
		{
			sem_wait(start_sem);
			routine(&table->philo[i]);
			break ;
		}
		//usleep(1000);
	}
	for (i = 0; i < table->num_philo; i++)
		sem_post(start_sem);
	i = 0;
	while (i < table->num_philo)
	{
		pid_t child_pid = waitpid(-1, &status, 0);
		if (child_pid == -1)
			break ;
		if (WIFSIGNALED(status))
		{
			int signal = WTERMSIG(status);
			if (signal == SIGTERM)
				continue;
		}
		i++;
	}
		sem_close(start_sem);
		sem_unlink("start");
}

bool	init_sems(t_table *table)
{
	sem_unlink("death");
	sem_unlink("print");
	sem_unlink("table");
	sem_unlink("forks");
	table->death_sem = sem_open("death", O_CREAT, 0600, 1);
	table->print_sem = sem_open("print", O_CREAT, 0600, 1);
	table->table_sem = sem_open("table", O_CREAT, 0600, 1);
	table->forks_sem = sem_open("forks", O_CREAT, 0600,
			table->num_philo);
	if (table->death_sem == SEM_FAILED || table->print_sem == SEM_FAILED
		|| table->table_sem == SEM_FAILED || table->forks_sem == SEM_FAILED)
		return (false);
	return (true);
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
	if (av[5])
		table->num_eat = ft_atoi(av[5]);
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
		table->philo[i].n_meal = 0;
		table->philo[i].table = table;
		table->philo[i].pid = -1;
	}
	return ;
}

int main(int ac, char **av)
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
	init_sim(&table);
	free(table.philo);
	return (0);
}
