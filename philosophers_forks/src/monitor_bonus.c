/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:29:37 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 12:36:51 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_philo		*ph;
	long long	nxt_death;
	t_state		*s;
	long long	i;

	ph = (t_philo *)arg;
	s = ph->s;
	while (!is_end(s))
	{
		usleep(1000);
		nxt_death = ph->nxt_death;
		if (now(&s->time, s) >= nxt_death && !is_end(s))
		{
			safe_print("died", ph, s);
			s->end = 1;
			i = 0;
			while (i < s->n_philos)
			{
				sem_post(s->sem_end);
				i++;
			}
			return (NULL);
		}
	}
	return (NULL);
}

void	*monitor_end(void *arg)
{
	t_state	*s;

	s = (t_state *)arg;
	sem_wait(s->sem_end);
	s->end = 1;
	return (NULL);
}
