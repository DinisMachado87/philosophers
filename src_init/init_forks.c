/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:44:59 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/01 02:44:44 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_state *s)
{
	ssize_t		i;

	i = 0;
	while (i < s->n_philos)
	{
		if (OK != track(&s->philos[i].track, FORK_MTX, s,
				pthread_mutex_init(&s->mtx_forks[i], NULL)))
			return (ERR);
		i++;
	}
	return (OK);
}
