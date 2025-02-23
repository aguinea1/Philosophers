/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:41:24 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/20 15:42:16 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

void	ft_error(char *error_str, void *var)
{
	if (var)
		free(var);
	if (error_str)
		printf(RED "%s" RESET, error_str);
	exit (EXIT_FAILURE);
}
