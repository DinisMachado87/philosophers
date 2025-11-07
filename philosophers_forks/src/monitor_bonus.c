/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:06:09 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 15:34:23 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	calc_time_left(t_philo *ph, t_state *s,
					long long *time_left, long long cached_now)
{
	if (OK != safe_sem_wait(s->sem_next_death))
		return (ERR);
	*time_left = ph->nxt_death - cached_now;
	if (OK != safe_sem_post(s->sem_next_death))
		return (ERR);
	return (OK);
}

void	*death_monitor(void *arg)
{
	t_philo			*ph;
	t_state			*s;
	long long		time_left;

	ph = (t_philo *)arg;
	s = ph->s;
	while (1)
	{
		calc_time_left(ph, s, &time_left, now(ph));
		if (time_left <= 0)
		{
			sem_wait(s->sem_write);
			printf("%lld %lld died\n", ph->cache_now - s->start, ph->id);
			close_semaphores(s);
			exit(DEAD);
		}
		if (time_left > 1)
			usleep(time_left * 1000);
		else
			usleep(time_left * 1000);
	}
	return (NULL);
}
