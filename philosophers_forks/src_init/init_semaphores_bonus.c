/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:20:09 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 12:43:22 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	safe_sem_open(sem_t **ptr, char *path, long long value, t_state *s)
{
	sem_unlink(path);
	*ptr = sem_open(path, O_CREAT, 0644, value);
	if (*ptr == SEM_FAILED)
		return (set_and_print_error(s, "Error: sem_open failed\n"));
	return (OK);
}

int	init_semaphores(t_state *s)
{
	if (OK != track(&s->track, SEM_FORKS, s,
			safe_sem_open(&s->sem_forks, "/philo_forks", s->n_philos, s))
		|| OK != track(&s->track, SEM_WRITE, s,
			safe_sem_open(&s->sem_write, "/philo_write", 1, s))
		|| OK != track(&s->track, SEM_END, s,
			safe_sem_open(&s->sem_end, "/philo_end", 0, s)))
		return (ERR);
	return (OK);
}
