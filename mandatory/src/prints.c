/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:29:53 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/23 23:47:12 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	what_is_the_flag(t_philo *philo, int flag)
{
	char	*status;

	pthread_mutex_lock(&philo->table->table_mtx);
	if (philo->table->philo_dead == true)
	{
		pthread_mutex_unlock(&philo->table->table_mtx);
		return ;
	}
	pthread_mutex_unlock(&philo->table->table_mtx);
	if (flag == EAT)
	{
		status = "is eating";
		printf(BLUE "%-6ld %d %s\n" RESET, get_time_ms(), philo->id, status);
	}
	else if (flag == FORK)
	{
		status = "has taken a fork";
		printf(CYAN "%-6ld %d %s\n" RESET, get_time_ms(), philo->id, status);
	}
	else if (flag == DIE)
	{
		status = "died";
	}
	else if (flag == THINK)
	{
		status = "is thinking";
		printf(YELLOW "%-6ld %d %s\n" RESET,  get_time_ms(), philo->id, status);
	}
	else if (flag == SLEEP)
	{
		status = "is sleeping";
		printf(MAGENTA "%-6ld %d %s\n" RESET, get_time_ms(), philo->id, status);
	}
	return ;
}

void	print_status(t_philo *philo, int flag)
{
	//pthread_mutex_lock(&philo->table->print_mtx);
	what_is_the_flag(philo, flag);
//	pthread_mutex_unlock(&philo->table->print_mtx);
}


