/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/27 17:28:48 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>

static int	safe_print(char *str, t_philo *ph)
{
	if (OK != pthread_mutex_lock(&ph->s->print)
		|| OK > printf("%d ", gettimeofday(&ph->s->tv, NULL))
		|| OK > printf(str, ph->id)
		|| OK != pthread_mutex_unlock(&ph->s->print))
		return (ERR);
	return (OK);
}

static int	eat(t_philo *ph, t_state *s)
{
	if (OK == pthread_mutex_lock(ph->fork_1)
		&& OK == safe_print("Philo %zu grabbed a fork!!!", ph)
		&& OK == pthread_mutex_lock(ph->fork_2)
		&& OK == safe_print("Philo %zu grabbed a fork!!!", ph)
		&& OK == safe_print("Philo %zu is eating!!!", ph)
		&& OK == wait_and_watch(s->t_eat, &s->end, &s->tv)
		&& OK == pthread_mutex_unlock(ph->fork_1)
		&& OK == pthread_mutex_unlock(ph->fork_2))
		return (OK);
	if (s->end)
		return (END);
	return (perror("Err: eat:"), ERR);
}

int	routine(void *philosopher)
{
	t_philo	*ph;
	t_state	*s;

	ph = (t_philo *)philosopher;
	s = ph->s;
	while (1)
	{
		if (OK != eat(ph, s)
			|| OK != safe_print("Philo %zu is sleeping!!!", ph)
			|| OK != wait_and_watch(s->t_sleep, &s->end, &s->tv)
			|| OK != safe_print("Philo %zu is thinking!!!", ph))
			break ;
	}
	if (s->end)
		return (END);
	return (OK);
}
