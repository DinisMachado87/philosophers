/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_state.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 23:00:57 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 20:28:33 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

inline static int	parse_attoll(long long *value, char *str,
							int allow_zero)
{
	*value = ft_atoll(str);
	if (*value < 0 || (!allow_zero && *value == 0))
	{

		printf("Err: arg '0' or not pos long long\n");
		return (ERR);
	}
	return (OK);
}

int	init_state(int argc, char **argv, t_state *s)
{
	s->end = 0;
	s->err = 0;
	if (OK != parse_attoll(&s->n_philos, argv[1], 0)
		|| OK != parse_attoll(&s->t_die, argv[2], 0)
		|| OK != parse_attoll(&s->t_eat, argv[3], 0)
		|| OK != parse_attoll(&s->t_sleep, argv[4], 0)
		|| (argc == 6
			&& OK != parse_attoll(&s->n_eats, argv[5], 1)))
	{
		s->n_philos = ERR;
		return (ERR);
	}
	if (argc == 5)
		s->n_eats = 0;
	return (OK);
}
