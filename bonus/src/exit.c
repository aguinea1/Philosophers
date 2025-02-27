/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:23:47 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/26 17:24:07 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus.h"

void	ft_error(char *error_str, void *var)
{
	if (var)
		free(var);
	if (error_str)
		printf(RED "%s" RESET, error_str);
	exit (EXIT_FAILURE);
}

