/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:42:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 10:51:43 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>

# define MALLOC_ERR "[philo bonus] Error: Memory allocation failed\n"
# define SEM_ERR "[philo bonus] Error: Semaphore creation failed\n"
# define FORK_ERR "[philo bonus] Error: Fork failed\n"
# define WRONG_ARGS "[philo bonus] Error: Wrong args\n"

// COLORS
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

typedef pthread_mutex_t	t_mtx;

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
	int				id;
	pid_t			pid;
	bool			dead;
	long			last_meal;
	unsigned int	next_meal;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	t_mtx	all;
	int		num_philo;
	int		full_philos;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	int		num_eat;
	int		n_meal;
	int		max_meals;
	bool	philo_dead;
	bool	all_meals;
	long	sim_start;
	sem_t	*forks_sem;
	sem_t	*death_sem;
	sem_t	*print_sem;
	sem_t	*table_sem;
	sem_t	*finish;
	t_philo	*philo;

}	t_table;

void	*monitor(void	*data);
void	sleep_act(t_philo *philo);
void	eat(t_philo *philo);
void	think(t_philo *philo);
void	print_status(t_philo *philo, int flag);
void	what_is_the_flag(t_philo *philo, int flag);
void	do_usleep(long ms);
bool	is_it_dead(t_philo *philo);
long	elapsed_time(t_philo *philo);
long	get_time_ms(void);
void	*routine(t_philo *philo);
void	ft_error(char *error_str, void *var);
int		parsing(int ac, char **arg);
int		ft_atoi(const char *nptr);
void	fork_act(t_philo *philo);
void	prep_sim(t_table *table);
void	init_struct(t_table *table, char **av);
bool	init_sems(t_table *table);
int		init_sim(t_table *table);
void	eat_lonely(t_philo *philo);
void	ph_end_processes(t_table *table);
#endif
