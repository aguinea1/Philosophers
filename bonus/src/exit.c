/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:23:47 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/10 10:45:25 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

void	ph_end_processes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (table->philo[i].pid > 0)
			kill(table->philo[i].pid, SIGKILL);
		i++;
	}
}

void	ft_error(char *error_str, void *var)
{
	if (var)
		free(var);
	if (error_str)
		printf(RED "%s" RESET, error_str);
	exit (EXIT_FAILURE);
}
