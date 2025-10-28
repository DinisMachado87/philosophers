/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/10/28 15:48:57 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philosopher)
{
	t_philo	*ph;
	t_state	*s;

	ph = (t_philo *)philosopher;
	s = ph->s;
	while (1)
	{
		if (OK != eat(ph, s)
			|| OK != safe_print("Philo %zu is sleeping!!!\n", ph, s)
			|| OK != wait_and_watch(s->t_sleep, s, &ph->time)
			|| OK != safe_print("Philo %zu is thinking!!!\n", ph, s))
			break ;
	}
	tracked_unlock(ph->fork_1, &locked[0], s);
	tracked_unlock(ph->fork_2, &locked[1], s);
	return (0);
}
