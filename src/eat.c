/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:25:40 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/01 04:30:27 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	lock_fork(pthread_mutex_t *fork, int *locked,
							t_philo *ph, t_state *s)
{
	if (OK == mtx_lock_tracked(fork, s))
	{
		*locked = 1;
		if (is_end(s))
			return (END);
		return (safe_print("has taken a fork\n", ph, s));
	}
	return (ERR);
}

static inline int	unlock_fork(
	pthread_mutex_t *fork, int *locked, t_state *s)
{
	if (*locked)
		mtx_unlock_tracked(fork, s);
	*locked = 0;
	return (OK);
}

static inline int	safe_update_last_meal(t_philo *ph, t_state *s)
{
	mtx_lock_tracked(&ph->mtx_philo, s);
	ph->nxt_death = now(&ph->time, s) + s->t_die;
	ph->n_eats++;
	mtx_unlock_tracked(&ph->mtx_philo, s);
	return (is_end(s));
}

int	eat(t_philo *ph, t_state *s)
{
	int		locked_1;
	int		locked_2;

	locked_1 = 0;
	locked_2 = 0;
	if (OK == lock_fork(ph->fork_1, &locked_1, ph, s)
		&& ph->fork_1 != ph->fork_2
		&& OK == lock_fork(ph->fork_2, &locked_2, ph, s)
		&& OK == safe_update_last_meal(ph, s)
		&& OK == safe_print("is eating\n", ph, s))
		wait_and_watch(s->t_eat, s, &ph->time);
	unlock_fork(ph->fork_1, &locked_1, s);
	unlock_fork(ph->fork_2, &locked_2, s);
	return (is_end(s));
}
