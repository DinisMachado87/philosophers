/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 15:25:40 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/28 16:02:58 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	tracked_lock(pthread_mutex_t *fork, int *locked,
							t_philo *ph, t_state *s)
{
	if (OK == pthread_mutex_lock(fork))
	{
		*locked = 1;
		if (is_end(s))
			return (END);
		if (OK == safe_print("Philo %lld grabbed a fork!!!\n", ph, s))
			return (OK);
	}
	return (set_and_print_error(s, "Err locking fork"));
}

static inline int	tracked_unlock(
	pthread_mutex_t *fork, int *locked, t_state *s)
{
	if (locked
		&& OK != pthread_mutex_unlock(fork))
		set_and_print_error(s, "Err unlocking fork\n");
	*locked = 0;
	return (is_end(s));
}

static inline void	safe_update_last_meal(t_philo *ph, t_state *s)
{
	pthread_mutex_lock(&ph->mtx_philo);
	ph->last_meal = now(&ph->time, s);
	ph->n_eats++;
	pthread_mutex_unlock(&ph->mtx_philo);
}

int	eat(t_philo *ph, t_state *s)
{
	int		locked[2];

	locked[0] = 0;
	locked[1] = 0;
	if (OK != tracked_lock(ph->fork_1, &locked[0], ph, s)
		|| OK != tracked_lock(ph->fork_2, &locked[1], ph, s)
		|| OK != safe_print("Philo %zu is eating!!!\n", ph, s))
	{
		wait_and_watch(s->t_eat, s, &ph->time);
	}
	tracked_unlock(ph->fork_1, &locked[0], s);
	tracked_unlock(ph->fork_2, &locked[1], s);
	safe_update_last_meal(ph, s);
	return (is_end(s));
}
