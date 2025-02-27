/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:16:55 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/26 20:06:18 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

static void	what_is_the_flag1(t_philo *philo, int flag)
{
	char	*status;

	if (flag == THINK)
	{
		status = "is thinking";
		printf(YELLOW "%-6ld %d %s\n" RESET, get_time_ms(), philo->id, status);
	}
	else if (flag == SLEEP)
	{
		status = "is sleeping";
		printf(MAGENTA "%-6ld %d %s\n" RESET, get_time_ms(), philo->id, status);
	}
	return ;
}

void	what_is_the_flag(t_philo *philo, int flag)
{
	char	*status;


	if (philo->table->philo_dead == true)
		return ;
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
	else
		what_is_the_flag1(philo, flag);
	return ;
}

void	print_status(t_philo *philo, int flag)
{
	sem_wait(philo->table->print_sem);
	what_is_the_flag(philo, flag);
	sem_post(philo->table->print_sem);
}

