/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/04 14:30:41 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	take_forks(t_philo *ph, t_state *s)
{
	int	forks_taken;

	forks_taken = 0;
	while (forks_taken < 2)
	{
		if (!(OK == safe_sem_wait(s->sem_forks) && forks_taken++)
			|| OK != safe_print("has taken a fork", ph, s))
		{
			while (forks_taken--)
				safe_sem_post(s->sem_forks);
			return (ERR);
		}
	}
	return (OK);
}

static void	if_philo_full_exit(t_state *s, t_philo *ph)
{
	if (s->n_eats > 0 && ph->n_eats >= s->n_eats)
	{
		close_semaphores(s);
		exit (FULL);
	}
}

static int	eat(t_philo *ph, t_state *s)
{
	ph->nxt_death = now(&ph->time) + s->t_die;
	wait_and_watch(s->t_eat, &ph->time, ph);
	ph->n_eats++;
	if_philo_full_exit(s, ph);
	if (OK == safe_sem_post(s->sem_forks)
		&& OK == safe_sem_post(s->sem_forks))
		return (OK);
	return (ERR);
}

void	philo_routine(t_philo *ph)
{
	t_state	*s;

	s = ph->s;
	free_and_null_pids(s);
	usleep(ph->id % 2 * s->t_eat * 500);
	while (OK == take_forks(ph, s)
		&& OK == safe_print("is eating", ph, s)
		&& OK == eat(ph, s)
		&& OK == safe_print("is sleeping", ph, s)
		&& OK == wait_and_watch(s->t_sleep, &ph->time, ph)
		&& OK == safe_print("is thinking", ph, s))
		;
	close_semaphores(s);
	exit (ERR);
}
