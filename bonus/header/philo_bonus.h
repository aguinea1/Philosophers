/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/25 16:53:18 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

# define MALLOC_ERR "[philo bonus] Error: Memory allocation failed\n"
# define SEM_ERR "[philo bonus] Error: Semaphore creation failed\n"

// COLORS
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

enum
{
	EAT,
	SLEEP,
	THINK,
	DIE,
	FORK,
};

typedef struct s_philo
{
	pid_t			pid;
	int				id;
	t_mtx			r_fork;
	t_mtx			*l_fork;
	bool			dead;
	long			last_meal;
	int				n_meal;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int		num_philo;
	int		full_philos;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	int		num_eat;
	t_mtx	table_mtx;
	t_mtx	print_mtx;
	bool	philo_dead;
	bool	all_meals;
	long	sim_start;
	t_philo	*philo;
}	t_table;


#endif
