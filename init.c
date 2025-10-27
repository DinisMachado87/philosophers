/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:00:57 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 17:01:15 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_forks(t_state *s)
{
	const char	*err_str = "ERR: init_forks:";
	ssize_t		i;

	i = 0;
	s->forks = malloc(s->n_philos * sizeof(pthread_mutex_t));
	if (!s->forks)
		return (perror(err_str), ERR);
	while (i < s->n_philos)
	{
		if (OK != pthread_mutex_init(&s->forks[i], NULL))
			return (perror(err_str), ERR);
		i++;
	}
	return (OK);
}

static void	assign_forks(t_philo *ph,
	pthread_mutex_t *right, pthread_mutex_t *left)
{
	if (ph->id % 2 == 0)
	{
		ph->fork_1 = right;
		ph->fork_2 = left;
	}
	else
	{
		ph->fork_1 = left;
		ph->fork_2 = right;
	}
}

static int	init_philos(t_philo **phs, t_state *s)
{
	const char	*err_str = "Err: init_philos: ";
	t_philo		*ph;
	size_t		i;

	i = 0;
	*phs = malloc(s->n_philos * sizeof(t_philo));
	if (!*phs)
		return (perror(err_str), ERR);
	ph = *phs;
	while (i++ < s->n_philos)
	{
		ph[i].id = i;
		ph[i].s = s;
		assign_forks(&ph[i],
			&s->forks[i - 1],
			&s->forks[(i + 1) % s->n_philos]);
		if (OK != pthread_create(&ph[i].life, NULL, routine, (void *)&ph[i]))
			return (perror(err_str), ERR);
	}
	return (OK);
}

inline static int	parse_attoll(long long *value, char *str, int allow_zero)
{
	*value = ft_atoll(str);
	if (*value <= 0 || (!allow_zero && *value == 0))
		return (printf("Err: arg '0' or not pos long long\n"), ERR);
	return (OK);
}

int	init_state(int argc, char **argv, t_state *s, t_philo **phs)
{
	const char	*err = "Usage: "
		"%s n_philo, t_die, t_eat, t_sleep, [opt:n_eats]\n";

	if (argc != 5 && argc != 6)
		return (printf(err, argv[0]), 0);
	if (OK != parse_attoll(&s->n_philos, argv[1], 0)
		|| OK != parse_attoll(&s->t_die, argv[2], 0)
		|| OK != parse_attoll(&s->t_eat, argv[3], 0)
		|| OK != parse_attoll(&s->t_sleep, argv[4], 0)
		|| argc == 6 && OK != parse_attoll(&s->n_eats, argv[5], 1))
		return (ERR);
	if (OK != pthread_mutex_init(&s->print, NULL)
		|| OK != init_forks(s)
		|| OK != init_philos(phs, s))
		return (ERR);
	return (OK);
}
