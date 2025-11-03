/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimachad <dimachad@student.42berlin.d>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 19:08:23 by dimachad          #+#    #+#             */
/*   Updated: 2025/11/02 13:10:53 by dimachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	take_forks(t_philo *ph, t_state *s)
{
	int	forks_taken;

	forks_taken = 0;
	while (forks_taken < 2)
	{
		if (!(OK == safe_sem_wait(s->sem_forks, s) && forks_taken++)
			|| OK != safe_print("has taken a fork", ph, s))
		{
			while (forks_taken--)
				safe_sem_post(s->sem_forks, s);
			return (ERR);
		}
	}
	return (is_end(s));
}

static int	eat(t_philo *ph, t_state *s)
{
	ph->nxt_death = now(&ph->time, s) + s->t_die;
	if (OK != safe_print("is eating", ph, s)
		|| OK != wait_and_watch(s->t_eat, s, &ph->time))
		return (ERR);
	ph->n_eats++;
	safe_sem_post(s->sem_forks, s);
	safe_sem_post(s->sem_forks, s);
	return (is_end(s));
}

static int	is_philo_full(t_state *s, t_philo *ph)
{
	if (s->n_eats > 0 && ph->n_eats >= s->n_eats)
	{
		s->end = 1;
		return (1);
	}
	return (0);
}

void	cleanup_child(t_state *s)
{
	if (s->sem_forks != SEM_FAILED)
		sem_close(s->sem_forks);
	if (s->sem_write != SEM_FAILED)
		sem_close(s->sem_write);
	if (s->pids)
		free(s->pids);
}

void	philo_routine(t_philo *ph)
{
	t_state	*s;

	s = ph->s;
	if (OK != track(&s->track, MONITOR_THRD, s,
			pthread_create(&ph->monitor_thread, NULL, monitor_death, ph))
		|| OK != track(&s->track, END_MONITOR_THRD, s,
			pthread_create(&ph->end_monitor_thread, NULL, monitor_death, ph)))
	{
		cleanup_child(ph->s);
		exit(ERR);
	}
	usleep(ph->id % 2 * s->t_eat * 500);
	while (!is_end(s)
		&& OK == take_forks(ph, s)
		&& OK == eat(ph, s)
		&& !is_philo_full(s, ph)
		&& OK == safe_print("is sleeping", ph, s)
		&& OK == wait_and_watch(s->t_sleep, s, &ph->time))
		safe_print("is thinking", ph, s);
	if (!is_end(s))
	{
		s->end = 1;
		sem_post(s->sem_end);
	}
	pthread_join(ph->monitor_thread, NULL);
	pthread_join(ph->end_monitor_thread, NULL);
	cleanup_child(ph->s);
	exit(s->n_eats > 0 && ph->n_eats >= s->n_eats);
}
