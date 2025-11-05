/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:05:22 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 02:06:40 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_pids_left(t_state *s)
{
	long long	i;

	i = 0;
	while (i < s->n_philos)
	{
		if (s->pids[i])
			kill(s->pids[i], SIGKILL);
		i++;
	}
}

void	unlink_semaphores(t_state *s)
{
	if (s->track & (1 << SEM_FORKS))
		sem_unlink("/philo_forks");
	if (s->track & (1 << SEM_WRITE))
		sem_unlink("/philo_write");
	if (s->track & (1 << SEM_DEATH))
		sem_unlink("/philo_death");
}

void	close_semaphores(t_state *s)
{
	if (s->track & (1 << SEM_FORKS))
		sem_close(s->sem_forks);
	if (s->track & (1 << SEM_WRITE))
		sem_close(s->sem_write);
	if (s->track & (1 << SEM_DEATH))
		sem_close(s->sem_death);
}

void	free_and_null_pids(t_state *s)
{
	if (s->pids)
		free(s->pids);
	s->pids = NULL;
}

void	free_all(t_state *s)
{
	close_semaphores(s);
	unlink_semaphores(s);
	kill_pids_left(s);
	free_and_null_pids(s);
}
