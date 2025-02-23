/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 09:34:39 by aguinea           #+#    #+#             */
/*   Updated: 2025/02/11 10:21:55 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philo.h"

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	result;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	while (*nptr == 32 || (8 < *nptr && *nptr < 14))
		nptr++;
	while (*nptr == '-' || *nptr == '+')
	{
		i++;
		if (*nptr == '-')
			sign = -1;
		nptr++;
		if (i >= 2)
			return (0);
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 +(*nptr - '0');
		nptr++;
	}
	return (result * sign);
}

static int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static	int	type_of_arg(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < ac)
	{
		j = 0;
		while (ft_isdigit(av[i][j]) && av[i][j])
			j++;
		if (av[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

static int	int_limit(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= INT_MAX && ft_atoi(av[i]) > 0)
			i++;
		else
			return (0);
	}
	return (1);
}

int	parsing(int	ac, char **arg)
{
	if (!type_of_arg(ac, arg) || !int_limit(ac, arg))
		return (printf("%s", WRONG_ARGS), 0);
	return (1);
}
