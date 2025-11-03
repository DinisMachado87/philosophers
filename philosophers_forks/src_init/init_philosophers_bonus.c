/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:59:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 05:47:26 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philosophers(t_state *s)
{
	long long	i;
	t_philo		ph;

	memset(s->pids, 0, sizeof(pid_t) * s->n_philos);
	i = 0;
	while (i < s->n_philos)
	{
		s->pids[i] = fork();
		if (s->pids[i] < 0)
			return (set_and_print_error(s, "Error: fork failed\n"));
		if (s->pids[i] == 0)
		{
			ph.id = i + 1;
			ph.nxt_death = s->start + s->t_die;
			ph.n_eats = 0;
			ph.s = s;
			philo_routine(&ph);
		}
		i++;
	}
	return (OK);
}
