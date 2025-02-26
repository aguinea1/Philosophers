/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:44:35 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/25 16:46:57 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo_bonus"



int main(int ac, char **av)
{
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
}
