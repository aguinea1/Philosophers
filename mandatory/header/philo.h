/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:41:55 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/21 00:25:58 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// LIBS
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

// COLORS
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

// ERRORS
# define WRONG_ARGS "Invalid args\n"
# define E_MALLOC "Error with malloc\n"
# define E_MTX "Error with mutex\n"

enum 
{
EAT, 
SLEEP, 
THINK,
DIE,
FORK,
};

typedef pthread_mutex_t	t_mtx;


typedef struct s_philo
{
	int				id;
	t_mtx			meal_flag;
	t_mtx			r_fork;
	t_mtx			*l_fork;
	bool			dead;
	long			last_meal;
	int				n_meal;
	pthread_t		thread;
	struct	s_table	*table;
}	t_philo;

typedef struct	s_table
{
	int		num_philo;
	int		tt_die;
	int		tt_eat;
	int		tt_sleep;
	int		num_eat;
	t_mtx	table_mtx;
	t_mtx	print_mtx;
	bool	philo_dead;
	bool	all_meals;
	long	sim_start;
	t_philo *philo;
}	t_table;

//INIT PHILO
int	parsing(int	ac, char **arg);
int	ft_atoi(const char *nptr);

//INIT SIMULATION
void	print_status(t_philo *philo, int flag);
void	*monitor(void *data);
void	*routine(void *philo);
void	what_is_the_flag(t_philo *philo, int flag);

//UTILS
void	do_usleep(long ms);
bool	is_it_dead(t_philo *philo);
bool	get_bool(t_mtx *data, bool *any, int flag);
long	elapsed_time(t_philo *philo);
long	get_time_ms(void);
void	ft_error(char *error_str, void *var);
void	destroy_mutex(t_table *table);
#endif
