/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:43:48 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/01 03:36:41 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>

static void	assign_forks(t_philo *ph,
	pthread_mutex_t *left, pthread_mutex_t *right)
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

int	init_philos(t_philo *ph, t_state *s)
{
	long long	i;
	int			right;

	i = 0;
	while (i < s->n_philos)
	{
		ph[i].track = 0;
		ph[i].id = i + 1;
		ph[i].s = s;
		ph[i].nxt_death = s->start + s->t_die;
		ph[i].n_eats = 0;
		right = (i + 1) % s->n_philos;
		assign_forks(&ph[i], &s->mtx_forks[i], &s->mtx_forks[right]);
		if (OK != track(&ph[i].track, PHILO_MTX, s,
				pthread_mutex_init(&ph[i].mtx_philo, NULL))
			|| OK != track(&ph[i].track, PHILO_THRD, s,
				pthread_create(&ph[i].life, NULL, routine, &ph[i])))
			return (ERR);
		i++;
	}
	return (OK);
}
