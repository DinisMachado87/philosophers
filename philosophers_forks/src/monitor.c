/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 15:06:09 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 02:15:29 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	*death_monitor(void *arg)
{
	t_philo		*ph;
	t_state		*s;
	long long	current_time;

	ph = (t_philo *)arg;
	s = ph->s;
	while (1)
	{
		usleep(1000);
		current_time = now(&ph->time);
		if (current_time >= ph->nxt_death)
		{
			sem_wait(s->sem_death);
			safe_print("died", ph, s);
			close_semaphores(s);
			exit(DEAD);
		}
	}
	return (NULL);
}
