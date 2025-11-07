/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 17:34:52 by dimachad         ###   ########.fr       */
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
			|| OK != safe_print("is sleeping", ph, s)
			|| OK != wait_and_watch(s->t_sleep, s, &ph->time)
			|| OK != safe_print("is thinking", ph, s))
			break ;
	}
	return (0);
}
