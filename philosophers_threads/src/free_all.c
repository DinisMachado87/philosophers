/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:05:22 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 20:33:34 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <unistd.h>

void	*free_and_null(void *ptr)
{
	if (ptr)
		free(ptr);
	return (NULL);
}

void	free_philos_and_forks(t_state *s)
{
	long long	i;

	i = 0;
	while (i < s->n_philos && s->philos)
	{
		if (s->philos[i].track & (1 << PHILO_THRD))
			pthread_join(s->philos[i].life, NULL);
		i++;
	}
	i = 0;
	while (i < s->n_philos && s->philos)
	{
		if (s->philos[i].track & (1 << FORK_MTX))
			pthread_mutex_destroy(&s->mtx_forks[i]);
		if (s->philos[i].track & (1 << PHILO_MTX))
			pthread_mutex_destroy(&s->philos[i].mtx_philo);
		i++;
	}
	s->philos = free_and_null(s->philos);
	s->mtx_forks = free_and_null(s->mtx_forks);
}

void	free_all(t_state *s)
{
	if (s->n_philos == 0 || s->n_philos == ERR)
		return ;
	free_philos_and_forks(s);
	if (s->track & (1 << STATE_MTX))
		pthread_mutex_destroy(&s->state_mtx);
}
