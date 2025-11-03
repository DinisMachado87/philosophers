/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:05:22 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 12:43:50 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup_semaphores(t_state *s)
{
	if (s->track & (1 << SEM_FORKS))
	{
		sem_close(s->sem_forks);
		sem_unlink("/philo_forks");
	}
	if (s->track & (1 << SEM_WRITE))
	{
		sem_close(s->sem_write);
		sem_unlink("/philo_write");
	}
	if (s->track & (1 << SEM_END))
	{
		sem_close(s->sem_end);
		sem_unlink("/philo_end");
	}
}

void	free_all(t_state *s)
{
	cleanup_semaphores(s);
	if (s->pids)
		free(s->pids);
}
