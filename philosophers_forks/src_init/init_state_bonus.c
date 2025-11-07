/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:00:57 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 13:56:09 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline int	parse_attoll(long long *value, char *str, int allow_zero)
{
	*value = ft_atoll(str);
	if (*value < 0 || (!allow_zero && *value == 0))
	{
		if (*value == 0)
			printf("Error: arg '0'\n");
		return (ERR);
	}
	return (OK);
}

int	init_state(int argc, char **argv, t_state *s)
{
	s->track = 0;
	s->pids = NULL;
	s->n_philos = 0;
	if (OK != parse_attoll(&s->n_philos, argv[1], 0)
		|| OK != parse_attoll(&s->t_die, argv[2], 0)
		|| OK != parse_attoll(&s->t_eat, argv[3], 0)
		|| OK != parse_attoll(&s->t_sleep, argv[4], 0)
		|| (argc == 6
			&& OK != parse_attoll(&s->n_eats, argv[5], 1)))
		return (ERR);
	if (argc == 5)
		s->n_eats = 0;
	s->start = now(NULL);
	if (OK != safe_calloc((void **)&s->pids, (sizeof(pid_t) * s->n_philos)))
		return (ERR);
	return (OK);
}
