/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:00:57 by dimachad          #+#    #+#             */
/*   Updated: 2025/09/30 19:07:07 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	ft_atoll(char *original)
{
	char		*str;
	long long	n;
	int			digit;

	str = original;
	n = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-')
		return (printf("Err: Negative arg: %s\n", original), ERR);
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str++ - '0';
		if (n > (LLONG_MAX - digit) / 10)
			return (printf("Err: ft_atoll overflow: %s\n", original), ERR);
		n = n * 10 + digit;
	}
	if (*str)
		return (printf("Err: Arg with invalid chars: %s\n", original), ERR);
	return (n);
}

int	init_state(int argc, char **argv, t_state *s)
{
	char *err = "Usage: %s n_philo, t_die, t_eat, t_sleep, [opt:n_eats]\n";

	if (argc != 5 && argc != 6)
		return (printf(err, argv[0]), 0);
	s->n_philos = ft_atoll(argv[1]);
	s->t_die = ft_atoll(argv[2]);
	s->t_eat = ft_atoll(argv[3]);
	s->t_sleep = ft_atoll(argv[4]);
	if (argc == 6)
		s->n_eats = ft_atoll(argv[5]);
	if (s->n_philos <= 0 || s->t_eat <= 0 || s->t_die <= 0
		|| s->t_sleep <= 0 || s->n_eats < 0)
		return (printf("Err: arg '0' or not pos long long\n"), ERR);
	return (1);
}
