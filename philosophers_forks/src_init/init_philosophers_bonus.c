/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:59:42 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 02:13:28 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_philosophers(t_state *s)
{
	long long	i;
	t_philo		ph;

	i = 0;
	while (i < s->n_philos)
	{
		s->pids[i] = fork();
		if (s->pids[i] < 0)
			return (ret_and_print_err("Error: fork failed\n"));
		if (s->pids[i] == 0)
		{
			ph.id = i + 1;
			ph.nxt_death = s->start + s->t_die;
			ph.n_eats = 0;
			ph.s = s;
			philo_routine(&ph);
		}
		usleep(100);
		i++;
	}
	return (OK);
}
