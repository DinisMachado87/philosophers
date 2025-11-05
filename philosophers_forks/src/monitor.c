/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:06:09 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 20:46:57 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	*death_monitor(void *arg)
{
	const long long	margin = 10;
	t_philo			*ph;
	t_state			*s;
	long long		current_time;
	long long		time_left;

	ph = (t_philo *)arg;
	s = ph->s;
	while (1)
	{
		current_time = now();
		if (current_time > ph->nxt_death)
		{
			sem_wait(s->sem_write);
			printf("%lld %lld died\n", current_time - s->start, ph->id);
			close_semaphores(s);
			exit(DEAD);
		}
		time_left = ph->nxt_death - current_time;
		if (time_left < margin)
			usleep(1000);
		else
			usleep(time_left * 800);
	}
	return (NULL);
}
