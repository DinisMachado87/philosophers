/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:20:09 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/05 02:14:00 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	safe_sem_open(sem_t **ptr, char *path, long long value)
{
	sem_unlink(path);
	*ptr = sem_open(path, O_CREAT, 0644, value);
	if (*ptr == SEM_FAILED)
		return (ret_and_print_err("Error: sem_open failed\n"));
	return (OK);
}

int	init_semaphores(t_state *s)
{
	if (OK != track(&s->track, SEM_FORKS,
			safe_sem_open(&s->sem_forks, "/philo_forks", s->n_philos))
		|| OK != track(&s->track, SEM_WRITE,
			safe_sem_open(&s->sem_write, "/philo_write", 1))
		|| OK != track(&s->track, SEM_DEATH,
			safe_sem_open(&s->sem_death, "/philo_death", 1)))
		return (ERR);
	return (OK);
}
