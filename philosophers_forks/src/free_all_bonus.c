/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:05:22 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/07 13:49:09 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	unlink_semaphores(t_state *s)
{
	if (s->track & (1 << SEM_FORKS))
		sem_unlink("/philo_forks");
	if (s->track & (1 << SEM_WRITE))
		sem_unlink("/philo_write");
	if (s->track & (1 << SEM_NEXT_DEATH))
		sem_unlink("/philo_next_death");
}

void	close_semaphores(t_state *s)
{
	if (s->track & (1 << SEM_FORKS))
		sem_close(s->sem_forks);
	if (s->track & (1 << SEM_WRITE))
		sem_close(s->sem_write);
	if (s->track & (1 << SEM_NEXT_DEATH))
		sem_close(s->sem_write);
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
